#include <iostream>
using namespace std;

#include "aerobicExercise.h"

//constructor
AerobicExercise::AerobicExercise(Device *d,  int minutes, int heartBeat): Exercise (d)
{
	this->minutes = minutes;
	this->heartBeat = heartBeat;
}

//sets
void AerobicExercise::setMinutes(int min)
{
	this->minutes = min;
}

void AerobicExercise::setHeartBeat(int hb)
{
	this->heartBeat = hb;
}

//gets
int AerobicExercise::getMinutes() const
{
	return this->minutes;
}

int AerobicExercise::getHeartBeat() const
{
	return this->heartBeat;
}

Exercise* AerobicExercise::clone() const
{
	Exercise * temp = new AerobicExercise(*this);
	return temp;
}