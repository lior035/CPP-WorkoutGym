#ifndef AEROBICDEVICE_H
#define AEROBICDEVICE_H

#include "device.h"

class AerobicDevice: public Device
{
	//private by defult
	double avgCalories;
	
	virtual void addToPrint (ostream& os) const
	{
		os<<"Aerobic device,";
		os<<"avarge calories per hour: "<<avgCalories<<endl;
	};

public:
	AerobicDevice (double avg = 0, const char * name = NULL);//constructor
	AerobicDevice (ifstream &inFile); // constructor by file
	AerobicDevice (const AerobicDevice & adToCopy);//copy constructor
	
	//sets
	void setAvg (double avgCalories);
	//gets
	double getAvg ()const;

	virtual void showSafetyInstructions () const;
	virtual void saveDeviceToFile (ofstream & outFile) const;
	virtual Device* clone () const;

};

#endif
