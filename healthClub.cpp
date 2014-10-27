#include <iostream>
using namespace std;
#include <string.h>
#include <typeinfo.h>
#include "healthClub.h"
#include "healthClubException.h"

HealthClub::HealthClub(char* name): devices(0) //constructor
{
	if (name!=NULL)
		this->setName(name);

	trainers = NULL;
	iTrainer = 0;
}

HealthClub::HealthClub(ifstream & inFile)//constructor by file
{
	//assumption - the file is open and set to be readen
	
	//Part 1- reading the club name and length 
	this->readClubName (inFile);
	
	//Part 2 - reading and creating the trainer array from the file
	this->readTrainer (inFile);

	//Part 3 - reading and creating the device array from the file
	this->readDevice (inFile);
}

void HealthClub:: readClubName (ifstream & inFile) // private function
{
	//assumption - the file is open to be readen
	int length;
	inFile.read((char*)&length,sizeof(length)); //reading the length of the club's name
	char* name = new char [length+1]; // allocating name string 
	inFile.read((char*)name, length);//read the name of the club from the file
	name[length] = '\0';
	this->setName(name);
	delete [] name;
}


void HealthClub:: readTrainer (ifstream & inFile)
{
	//assumption - the file is open and set on the right place
	int i;

	int totalTrainer;
	inFile.read((char*)&totalTrainer, sizeof(totalTrainer)); // reading the total amount of trainers in the club
	this->iTrainer = totalTrainer;	

	this->trainers = new Trainer* [iTrainer]; //allocating trainer * array

	//creating the trainers according the info in the file
	for (i = 0; i<iTrainer; i++)
		*(this->trainers+i) = new Trainer (inFile);
}

void HealthClub::readDevice (ifstream & inFile)
{
	//assumption - the file is open and set on the right place
	int i;

	int Serial;
	inFile.read((char*)&Serial, sizeof(Serial));//reading the serial number of device
	Device::SetSerialNum(Serial);
	
	int totalDevice;
	inFile.read((char*)&totalDevice, sizeof(totalDevice)); //reading the total amount of devices in the club

	this->devices.setLogicSize(totalDevice); //allocating device* array
	this->devices.getArray() = new Device*[totalDevice];

	//creating the devices according the info in the file 
	for (i = 0; i<this->devices.getLogicSize(); i++)
	{
		int length = 3;
		char* type = new char [length+1]; //indicate the type of the current device
		inFile.read((char*)type,length); // read the type of current device from the file
		type[length]= '\0';
		if (strncmp(type,typeid(AerobicDevice).name()+6, length) == 0)
		{
			Device* d = new AerobicDevice (inFile); // create from the file new aerobic device
			this->devices.replaceCell(i,d);
		}
		else if (strncmp(type,typeid(PowerDevice).name()+6,length) == 0)
		{
			Device* d =  new PowerDevice (inFile); // create from the file new Power device
			this->devices.replaceCell(i,d);
		}
	}
}

HealthClub:: HealthClub(const HealthClub& clubToCopy): devices(clubToCopy.devices.getLogicSize()), trainers(NULL)//copy constructor
{
	*this = clubToCopy;
}

//operator = overload for private use only
HealthClub& HealthClub:: operator= (const HealthClub & h)
{
	//assumption - devices and trainers will always be NULL at this point - since the operator = 
	//is being used only in the copy onstructor

	int i;
	this->iTrainer = h.iTrainer;

	this->trainers = new Trainer * [iTrainer];

	for (i = 0; i<devices.getLogicSize(); i++)
	{
		Device * d =  h.devices[i]->clone();
		this->devices.replaceCell(i,d);
	}
	for (i = 0; i<iTrainer; i++)
		this->trainers[i] = new Trainer (*(h.trainers[i]));

	this->setName(h.getClubName());

	return *this;
}

//sets

void  HealthClub:: setName (const char * name)
{
	strncpy (clubName, name,LengthTotal);
	clubName[LengthTotal] = '\0';
}

//gets

const char* HealthClub:: getClubName () const
{
	return clubName;
}

int HealthClub:: getTotalTrainerCount () const
{
	return iTrainer;
}

int HealthClub:: getTotalDeviceCount () const
{
	return devices.getLogicSize();
}

//2 ways for getting pointer for a specific trainer:
Trainer* HealthClub:: getTrainer (const char* tName) const
{
	int i;

	if (iTrainer == 0)
	{
		cout<<"There are no trainers at all in the club"<<endl;
		return NULL;
	}

	for (i = 0; i<iTrainer; i++)
	{
		if (strcmp(trainers[i]->getName(), tName) == 1)
			return trainers[i];
	}

	cout<<"No trainer with that name"<<endl;
	return NULL;
}

Trainer* HealthClub:: getTrainer (int index) const throw(HealthClubException*)
{
	if (index>=iTrainer)
	{
		HealthClubException * hce = new HealthClubException(NULL,INDEX_OUT_OF_BOUNDRIES);
		throw hce;
	}
	return trainers[index];
}

//2 ways for getting pointer for a specific device:
Device* HealthClub:: getDevice (const char* dName) const
{
	int i;
	if (devices.getLogicSize() == 0)
	{
		cout<<"There are no devices at all in the club"<<endl;
		return NULL;
	}

	for (i=0; i<devices.getLogicSize(); i++)
	{
		if (strcmp(devices[i]->getName(),dName) == 1)
			return devices[i];
	}

	cout<<"No device with that name"<<endl;
	return NULL;
}

Device* HealthClub:: getDevice (int index) const
{
	//see comment 6 (-2)
	if (index>=devices.getLogicSize())
		return NULL;
	return devices[index];
}

//add

int HealthClub:: addTrainer (char* newTrainerName)throw(HealthClubException* )
{
	if (iTrainer>=100)
	{
		HealthClubException* hce = new HealthClubException(newTrainerName,REGISTER_FAILED_CLUB_IS_FULL) ;
		throw hce;
	}

	else if (trainerIsAlreadyIn(this->trainers, this->iTrainer, newTrainerName))
	{
		HealthClubException* hce = new HealthClubException (newTrainerName, REGISTER_FAILED_CANNOT_DUPLICATE_TRAINER);
		throw hce;
	}

	else
	{
		(*this).extandTrainersArrey(newTrainerName);
		return REGISTER_SUCCEED;
	}
}

//2 private sub method for addTrainer to use:
bool HealthClub:: trainerIsAlreadyIn(Trainer** trainers, int iTrainer, const char* trainerName)const
{
	int i =0;

	if (iTrainer == 0) //Means that there are not any trainers (now - trainers points to NULL)
		return false;

	for (i=0; i<iTrainer; i++)
	{
		if (strcmp(trainerName, trainers[i]->getName())==0)
			return true;
	}
	return false;
}

void HealthClub:: extandTrainersArrey(char* newTrainerName)
{
	//see comment 12 (-2)
	//see comment 19 (-3)
	int i = 0;

	Trainer ** newArr;
	this->iTrainer++;

	newArr = new Trainer * [this->iTrainer];
	for (i=0; i<this->iTrainer-1; i++)
	{
		newArr[i] = new Trainer;
		newArr[i]->setName(this->trainers[i]->getName());
		newArr[i]->getProgram() = this->trainers[i]->getProgram();
	}

	newArr[i] = new Trainer;
	newArr[i]->setName(newTrainerName);
	newArr[i]->setProgram();

	for (i=0; i<iTrainer-1; i++)
		delete  this->trainers[i];
	delete [] this->trainers;

	this->trainers = newArr;
}

bool HealthClub :: addDevice (Device* newDevice)
{
	if (newDevice == NULL)
		return false;

	if (deviceIsAlreadyIn(this->devices, newDevice))
	{
		cout<<newDevice->getName()<<" is already at our club"<< endl;
		return false;
	}

	else
	{
		this->extandDevicesArrey(this->devices,newDevice);
		return true;
	}
}

//2 private sub method for addDevice to use:
bool HealthClub:: deviceIsAlreadyIn(Array<Device>&devices,  Device* newDevice) const
{
	int i = 0;

	if (devices.getLogicSize() == 0) //Means that there are not any devices (now - devices points to NULL)
		return false;

	for (i = 0; i<devices.getLogicSize(); i++)
	{
		if (strcmp(newDevice->getName(), devices[i]->getName())==0)
			return true;
	}
	return false;
}

void HealthClub:: extandDevicesArrey(Array<Device>& arr, Device* newDevice)
{
	int i = 0;

	Device** newArr;

	int total = this->devices.getLogicSize();
	total++;

	newArr = new Device * [total];
	for (i=0; i<total-1; i++)
	{
		newArr[i] = arr[i]->clone();
	}


	//Device::SetSerialNum(current->iDevice-1, '-');
	//not needed - the son make sure that while cloning the SerialNum will not be increased

	newArr[i] = newDevice->clone();

	for (i=0; i<this->devices.getLogicSize();i++)
		delete this->devices[i];

	devices.setLogicSize(devices.getLogicSize()+1);
	for (i=0; i<total; i++)
		arr.replaceCell(i, newArr[i]);
	
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const HealthClub& h)
{
	int i;
	os<<"Club name : " <<h.clubName<<endl<<endl;
	os<<"Number of trainers in the club : "<<h.iTrainer<<endl;
	if (h.iTrainer!=0)
		os<<"Trainers : "<<endl;

	for (i= 0; i<h.iTrainer; i++)
		os<<i+1<<"). "<<*(h.trainers)[i];

	os<<endl;

	int total = h.devices.getLogicSize();
	os<<"Number of devices in the club : "<<total<<endl;
	if (total!=0)
		os<<"Devices : "<<endl;

	for (i= 0; i<total; i++)
		os<<i+1<<"). "<<(*(h.devices[i]));
	return os;
}

//-----------------------------------------------------------------

void HealthClub:: saveToFile (const HealthClub & hToSave, ofstream & outFile) const
{
	//assumption - the file is open and ready to be use
	int i, length, totalTrainer, totalDevice;

	//writing the club name
	length = strlen(hToSave.getClubName());

	outFile.write((const char *) &length, sizeof (length)); //writing the length of the club name
	outFile.write((const char*)hToSave.getClubName(), length); // writing the name of the club

	//writing the trainers detaile (only name):
	totalTrainer = hToSave.getTotalTrainerCount();
	outFile.write((const char*) &totalTrainer, sizeof (totalTrainer));//writing the amount of trainers

	for (i = 0; i<totalTrainer; i++)
	{
		char * tName = hToSave.getTrainer(i)->getName(); //excption is not needed here since the i is alyays in the boundries
		length = strlen(tName);
		outFile.write((const char *)&length, sizeof(length));//writing the length of the name of current trainer
		outFile.write((const char *)tName, length); //writing the name of current trainer
	}

	int Serial = Device::GetSerialNum();
	
	outFile.write((const char *)&Serial, sizeof(Serial)); //writing the last serial number

	//writing the device detail:
	totalDevice = hToSave.devices.getLogicSize();
	outFile.write((const char*)&totalDevice, sizeof (totalDevice)); // writing the amount of devices

	for (i = 0; i<totalDevice; i++)
	{
		Device* d = hToSave.devices[i]; // getting the current device to save
		d->saveDeviceToFile(outFile); //will save to the file: 1)device type, 2)serial of current device 
									  //             3) device length, 4)device name, 5)extra information according the device type
	}
}

//---------------------------------------------------------------------

HealthClub::~HealthClub() // destructor
{		
	delete [] trainers;
}//here it will enter the Array<T> destructor