#include <iostream>
using namespace std;

#include "powerExercise.h"

//constructor
PowerExercise ::PowerExercise(Device* d , int numOfSets, int rehearsalsInSet ): Exercise(d)
{
	this->numOfSets = numOfSets;
	this->rehearsalsInSet = rehearsalsInSet;
}

//sets
void PowerExercise:: setNumOfSets (int num)
{
	this->numOfSets = num;
}

void PowerExercise:: setNumOfRehearsel(int num) 
{
	this->rehearsalsInSet = num;
}

//gets
int PowerExercise:: getNumOfSets () const
{
	return this->numOfSets;
}

int PowerExercise:: getNumOfRehearsel () const
{
	return this->rehearsalsInSet;
}

Exercise* PowerExercise::clone() const
{
	Exercise* temp = new PowerExercise(*this);
	return temp;
}