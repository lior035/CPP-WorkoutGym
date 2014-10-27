#ifndef PROGRAM_H
#define PROGRAM_H
#include "date.h"
#include "exercise.h"
#include "device.h"
#include "array.h"
	
class Program
{
	//private by defult
	Date lastUpdate;
	Array<Exercise>allExercise;
	void extandExerciseArray(Program * current, Exercise * e);
	
	
public:
	enum kindOfExercise
	{
		ALL_EXERCISE ,
		POWER_EXERCISE,
		AEROBIC_EXERCISE,
	};

	Program ();//constructor
    Program (const Program & pToCopy);// copy constructor 
	Program& operator = (const Program & p); // overload = operator

	//sets

	void setDate (const Date & currentDate);

	//gets

	Date getDate() const;
	Exercise ** getExercise() ;
	int getIndCurr () const;

	//Data member - allExercise: methods

	bool exerciseNotInProgram (const Exercise & e) ;
	Exercise * getExerciseByDeviceName (const char * deviceName);

	//overload operator
	bool operator+= (Exercise* e);// overload function for += (replacing addExerciseToProgram)
	bool operator-= (Exercise* e);// overload function for -= (replacing removeExerciseFromProgram)
	Exercise * operator[] (int index); // overload function for []

	// friend function
	friend ostream& operator<< (ostream & os, const Program& p); //operator << overload by friend function
	
	void show () const;
	void printSpecificKind (int kind = 0) const;
};
#endif //Program