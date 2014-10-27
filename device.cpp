#include <iostream>
using namespace std;
#include <string.h>
#include "device.h"

Device::Device(const char * name)//constructor
{
	if (name == NULL)
		this->name[0] = '\0';
	else
	{
		strncpy(this->name,name,TOTALLENGTH);
		this->name[TOTALLENGTH] = '\0';
	}

	serialNum = SerialNumber++;
}

Device::Device(ifstream& inFile)
{
	int serialCurr;
	inFile.read((char*)&serialCurr,sizeof(serialCurr));//will read the serial of the current device
	this->setSerialOfCurr(serialCurr);

	int length;
	inFile.read((char*)&length,sizeof(length));//will read the length of the name of the current device
	char* name = new char [length+1];
	inFile.read((char*)name, length);//will read  the name of the current device
	name[length] = '\0';
	this->cpyName(name);
	delete [] name;
}

//sets

void Device:: setName ()
{
	cin>>*this;
}

void Device:: setName (const char * name)//choose one of the 2 ways to set the device name
{
	if (this->name[0] == '\0')
	{
		if (name != NULL)
		{
			strncpy(this->name, name, TOTALLENGTH);
			this->name[TOTALLENGTH] = '\0';
		}
		else
			(*this).setName();
	}
}

void Device:: cpyName (const char* name)
{
	if (name!=NULL)
	{
		strncpy(this->name,name,TOTALLENGTH);
		this->name[TOTALLENGTH] = '\0';
	}
}

void Device:: setSerialOfCurr(int newSer)
{
	serialNum = newSer;
}

void Device::SetSerialNum(int offset, char position)
{
	if (position == '+')
		SerialNumber += offset;
	else
		SerialNumber -= offset;

} 

void Device::SetSerialNum(int newSerial)
{
	Device::SerialNumber = newSerial;
}

//gets

const char * Device:: getName () const
{
	return name;
}

int Device:: getSerialOfCurr () const 
{
	return serialNum;
}

int Device::GetSerialNum() 
{
	return SerialNumber;
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const Device& d)
{
	os<<"Device name : "<<d.getName()<<endl;
	os<<"Device serial number : "<<d.getSerialOfCurr()<<endl;
	d.addToPrint(os);
	return os;
}

//operator >> overload by friend function
istream& operator>> (istream & is, const Device& d)
{

	cout<<"Device name (maximum 20 characters)"<<endl;
	is.getline((char*)(d.getName()),TOTALLENGTH);

	return is;
}

//saving the device to the file
void Device:: saveDeviceToFile (ofstream & outFile) const
{
	//assumption - the file is open and ready to be used
	int length = 3;
	int serial = this->getSerialOfCurr();
	char* type = new char [length +1];

	//finding and writing the device type to the file
	strncpy(type,typeid(*this).name()+6, 3);
	outFile.write((const char*) type, length); // writing the type of the device

	outFile.write((const char*)&serial, sizeof(serial));//writing the device serial number
	
	//writing the device length and name
	length = strlen(this->getName());
	outFile.write((const char *)&length, sizeof(length));
	outFile.write((const char *)this->getName(),length);
}

void Device::show() const 
{
	cout<<*this;//re use
}

//set static variable
int Device:: SerialNumber = 1000;