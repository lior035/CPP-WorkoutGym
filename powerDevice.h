#ifndef POWERDEVICE_H
#define POWERDEVICE_H

#include "device.h"


class PowerDevice: public Device
{
	//private by defult
	char*  mainMuscles;

	virtual void addToPrint (ostream& os) const 
	{
		os<<"Power device, ";
		os<<"Works on: "<<mainMuscles;
	};

public:
	PowerDevice (const char* pName = NULL, const char * name = NULL);//constructor
	PowerDevice (ifstream & inFile);//constructor by file
	PowerDevice (const PowerDevice & pToCopy);//copy constructor
	
	//sets
	void setMM (const char*  pName);
	//gets
	char* getMM ()const;

	//operator = overload
	PowerDevice& operator= (const PowerDevice & pd);

	//virtuals 
	virtual void showSafetyInstructions () const;
	virtual void saveDeviceToFile (ofstream & outFile) const;
	virtual Device* clone () const;

	//destructor
	virtual ~PowerDevice ();
};

#endif
