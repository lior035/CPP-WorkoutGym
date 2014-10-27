#ifndef HEALTHCLUB_H
#define HEALTHCLUB_H
#define LengthTotal 20

#include <fstream>
#include "array.h"
#include "device.h"
#include "AerobicDevice.h"
#include "PowerDevice.h"
#include "trainer.h"
#include <vector>

class HealthClub
{
	typedef vector<Trainer*> tVector;

	//private by defult
	char clubName [LengthTotal+1] ;
	Trainer ** trainers;
	tVector traineres;
	Array<Device> devices;
	//see comment 14 (-1)
	int iTrainer;

	//in-class methods, for private use only 

	//2 private sub method for addTrainer to use
	bool trainerIsAlreadyIn(Trainer** trainers, int iTrainer, const char * trainerName) const;
	void extandTrainersArrey(char* newTrainerName);

	//2 private sub method for addDevice to use
	bool deviceIsAlreadyIn(Array<Device> &devices, Device* newDevice) const;
	void extandDevicesArrey(Array<Device> &arr, Device* newDevice);

	//3 private sub methods for the constructor which using the file
	void readClubName (ifstream & inFile);
	void readTrainer (ifstream & inFile);
	void readDevice (ifstream& inFile);

	//operator = overload in private
	HealthClub& operator= (const HealthClub & h);

public:
	enum exceptions
	{
		REGISTER_FAILED_CLUB_IS_FULL ,
		REGISTER_FAILED_CANNOT_DUPLICATE_TRAINER,
		INDEX_OUT_OF_BOUNDRIES,
		REGISTER_SUCCEED,
	};

	HealthClub(char * name = NULL);//Constructor
	HealthClub(ifstream & inFile);
	HealthClub (const HealthClub& clubToCopy);//copy constructor

	//sets

	void setName (const char * name);

	//gets

	const char* getClubName () const;
	int getTotalTrainerCount () const;
	int getTotalDeviceCount () const;

	//2 ways for getting pointer for a specific trainer:
	Trainer* getTrainer (const char* tName) const;
	Trainer* getTrainer (int index) const ;
	//2 ways for getting pointer for a specific device:
	Device* getDevice (const char* dName) const;
	Device* getDevice (int index) const;
	

	//add

	int addTrainer (char* newTrainerName);
	bool addDevice (Device* newDevice);

	//operator << overload by friend function
	friend ostream& operator<< (ostream & os, const HealthClub& h);

	void saveToFile (const HealthClub & hToSave, ofstream & outFile) const;

	~HealthClub (); //destractor
	
	
};

#endif 