#ifndef AEROBICEXERCISE_H
#define AEROBICEXERCISE_H

#include "exercise.h"

class AerobicExercise: public Exercise
{
	//private by defult
	int minutes;
	int heartBeat;

	virtual void addToPrint (ostream& os) const
	{
		os<<"This is Aerobic exercise!"<<endl;
		os<<"Minutes: "<<minutes<<", heart beat: "<<heartBeat<<endl;
	}

public:

	//constructor
	AerobicExercise (Device* d =NULL, int minutes = 0, int heartBeat = 0);

	//sets
	void setMinutes (int min);
	void setHeartBeat (int hb);

	//gets
	int getMinutes () const;
	int getHeartBeat() const;

	virtual Exercise* clone ()const;
};

#endif
