#include <iostream>
using namespace std;

#include "exercise.h"

Exercise:: Exercise (Device* device) : relatedDevice(NULL)//constructor
{
	if (device != NULL)
		relatedDevice = device->clone();
}

Exercise::Exercise(const Exercise &EtoCpy) : relatedDevice (NULL) // copy constructor
{
	*this = EtoCpy;//Re-use
}

Exercise& Exercise:: operator= (const Exercise & E) // private overload of operator =
{
	if (this != &E)
	{
		delete this->relatedDevice;
		relatedDevice = E.getDevice()->clone();
		return *this;
	}
	return *this;
}

//sets

void Exercise :: setDevice (Device * d1)
{
	if (d1 != NULL)
	{
		if (relatedDevice == NULL)
			relatedDevice = d1->clone();

		else
		{
			delete relatedDevice;
			relatedDevice = d1->clone();
		}
	}
}

//gets

const Device* Exercise :: getDevice ()const
{
	return relatedDevice;
}

Device* Exercise :: getDevice ()
{
	return relatedDevice;
}

void Exercise:: createExercise(Device* d)
{
	this->setDevice(d);
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const Exercise& e)
{
	e.addToPrint(os);
	os<<"Related device : "<<endl;
	os<<*(e.getDevice())<<endl;
	return os;
}
	
Exercise* Exercise::clone() const
{
	Exercise * temp = new Exercise (*this);
	return temp;
}

void Exercise :: show () const
{
	cout<<*this; // re use
}

Exercise::~Exercise() //destructor
{
	if (relatedDevice != NULL)
		delete [] relatedDevice;
}




