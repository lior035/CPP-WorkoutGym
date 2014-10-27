#include <iostream>
#include <string.h>
using namespace std;

#include "powerDevice.h"

//constructor
PowerDevice::PowerDevice (const char * pName, const char * name):Device(name)
{
	this->mainMuscles = new char [strlen(pName)+1];
	strcpy(this->mainMuscles,pName);
}

PowerDevice::PowerDevice(ifstream & inFile) : Device(inFile)//constructor by file
{
	//Assumption - the file is open and set in the correct place to start read the information

	//read the extra information for this type of device
	int length;
	inFile.read((char*)&length,sizeof(length));//reading the length of the main muscle name
	char * name = new char [length+1];
	inFile.read((char*)name,length);//read the extra information of this type of device from the file
	name[length] = '\0';
	this->mainMuscles = NULL;
	this->setMM(name);
	delete [] name;
}

//copy constructor 
PowerDevice::PowerDevice(const PowerDevice &pToCopy): Device ()
{
	Device::SetSerialNum(1,'-');
	this->mainMuscles = NULL;

	*this = pToCopy;
}

//sets

void PowerDevice:: setMM (const char*  pName)
{
	if (this->mainMuscles !=NULL)
		delete [] this->mainMuscles;
	this->mainMuscles = new char [strlen(pName+1)];
	strcpy (this->mainMuscles, pName);
}

//gets
char* PowerDevice:: getMM ()const
{
	return this->mainMuscles;
}

//operator = overload
PowerDevice& PowerDevice::operator =(const PowerDevice &pd)
{
	if (this != &pd)
	{
		Device::operator=(pd); //entering the defult =operator of device
		delete [] this->mainMuscles;
		this->mainMuscles = new char [strlen(pd.getMM())+1];
		strcpy(this->mainMuscles,pd.getMM());
	}
	return * this;
}

//virtuals
void PowerDevice::showSafetyInstructions() const
{
	cout<<"Caution: this device works on "<<this->getMM()<<", advised by your doctor if it suitable for you"<<endl;
}

void PowerDevice:: saveDeviceToFile (ofstream & outFile) const
{
	//saving the base details to the file
	Device::saveDeviceToFile(outFile);
	//writing extra information for this type of devices
	int length = strlen(this->getName());
	outFile.write((const char *)&length, sizeof(length));
	outFile.write((const char *)this->getName(),length);
}

Device* PowerDevice::clone() const
{
	return new PowerDevice(*this);
}

//destructor
PowerDevice::~PowerDevice () 
{
	delete [] mainMuscles;
}