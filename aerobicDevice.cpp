#include <iostream>
using namespace std;

#include "aerobicDevice.h"

//constructor
AerobicDevice::AerobicDevice(double avg, const char * name): Device(name)
{
	this->avgCalories = avg;
}

AerobicDevice::AerobicDevice(ifstream& inFile) : Device(inFile)//constructor by file
{
	//Assumption - the file is open and set in the correct place to begin reaf from

	//reading  the extra information after the base was readen
	double avg;
	inFile.read((char*)&avg, sizeof(avg));//reading the extra information for this type of device
	this->setAvg(avg);
}

//copy constructor
AerobicDevice::AerobicDevice (const AerobicDevice & adToCopy): Device (adToCopy.getName())
{
	this->avgCalories = adToCopy.avgCalories;
	this->setSerialOfCurr(adToCopy.getSerialOfCurr());
	Device::SetSerialNum(1,'-');
}

//sets
void AerobicDevice:: setAvg (double avgCalories)
{
	this->avgCalories = avgCalories;
}

//gets
double AerobicDevice::getAvg ()const
{
	return this->avgCalories;
}

//virtuals
void AerobicDevice:: showSafetyInstructions () const
{
	cout<<"Notice - this device helps you decrese "<<this->avgCalories<<" in an hour"<<endl;
}

void AerobicDevice:: saveDeviceToFile (ofstream & outFile) const
{
	//saving the base details to the file
	Device::saveDeviceToFile(outFile);
	//writing extra information for this type of devices
	double avg = this->getAvg();
	outFile.write((const char*)&avg, sizeof (avg));
}
	
Device* AerobicDevice::clone() const
{
	return new AerobicDevice (*this);
}