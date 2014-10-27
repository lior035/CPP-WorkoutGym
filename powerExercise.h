#ifndef POWEREXERCISE_H
#define POWEREXERCISE_H

#include "exercise.h"

class PowerExercise: public Exercise
{
	//private by defult
	int numOfSets;
	int rehearsalsInSet;

	virtual void addToPrint (ostream& os) const
	{
		os<<"This is a Power exercise!"<<endl;
		os<<"Number of sets: "<<numOfSets<<", "<<rehearsalsInSet<<" times."<<endl;
	}
	
public:

	//constructor
	PowerExercise (Device* d = NULL, int numOfSets = 0, int rehearsalsInSet = 0);

	//sets
	void setNumOfSets (int num);
	void setNumOfRehearsel (int num);

	//gets
	int getNumOfSets () const;
	int getNumOfRehearsel () const;

	virtual Exercise* clone () const;

};

#endif