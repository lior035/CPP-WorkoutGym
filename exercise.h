#ifndef EXERCISE_H
#define EXERCISE_H
#include "device.h"
#include <iostream>
using namespace std;

class Exercise
{
	//protectes in order to be used in derived
protected:

	Device * relatedDevice;
	Exercise& operator= (const Exercise & E); // Private operator = overload

	virtual void addToPrint (ostream& os) const
	{
	};

public:
	Exercise (Device * d = NULL);//Constructor
	Exercise (const Exercise& EtoCpy);// copy constructor

	//sets

	void setDevice (Device * d1);

	//gets

	const Device* Exercise :: getDevice ()const;
	Device* getDevice ();
	
	void createExercise(Device* d);

	//operator << overload by friend function
	friend ostream& operator<< (ostream & os, const Exercise& e);
	
	virtual Exercise* clone() const;

	void show () const;

	virtual ~Exercise ();//destructor
};

#endif 
