#include <iostream>
#include <typeinfo.h>
using namespace std;

#include "Program.h"
#include "exercise.h"
#include "powerExercise.h"
#include "aerobicExercise.h"

Program:: Program (): allExercise(0) // constructor
{
	Date d;
	lastUpdate.setDay(d.getToday().getDay());
	lastUpdate.setMonth(d.getToday().getMonth());
	lastUpdate.setYear(d.getToday().getYear());
}

Program:: Program (const Program & pToCopy): allExercise(0)// copy constructor
{
	*this = pToCopy;
}

Program& Program:: operator = (const Program & p) // operator = overload 
{
	if (this != &p)
	{
		int i;

		//step 1 - delete the previous values of this
		for (i=0; i<this->allExercise.getLogicSize(); i++)
			delete this->allExercise[i];

		//step 2 - check before copy;
		if (p.allExercise.getLogicSize()==0) // also means that indCurrNumOfExercise of p = 0 -> no exercise at all
			this->allExercise.setLogicSize(0);
		else
			//step 3 - copy the exercises (deep copy and not shallow)
		{
			this->allExercise.getArray() = new Exercise * [p.allExercise.getLogicSize()];
			this->allExercise.setLogicSize(p.allExercise.getLogicSize());

			for (i=0; i<p.allExercise.getLogicSize(); i++)
				this->allExercise.replaceCell(i, new Exercise (p.allExercise[i]->getDevice()));
		}

		//step 4 - copy the rest of the program
		this->setDate(p.getDate());

		//step 5 - return this
		return *this;
	}

	return *this;
}

//sets

void Program:: setDate (const Date & currentDate)
{
	lastUpdate.setDay(currentDate.getDay());
	lastUpdate.setMonth(currentDate.getMonth());
	lastUpdate.setYear(currentDate.getYear());
}

//gets

Date Program:: getDate() const
{
	return lastUpdate;
}

Exercise ** Program:: getExercise() 
{
	return allExercise.getArray();
}

int Program:: getIndCurr () const
{
	return this->allExercise.getLogicSize();
}

//Data member - allExercise: methods

void Program::extandExerciseArray(Program * current, Exercise* e)
{
	int i;
	int size = current->allExercise.getLogicSize();
	Exercise ** newArr;
	current->allExercise.setLogicSize(size+1);

	newArr = new Exercise * [size];
	for(i=0; i<size-1; i++)
		newArr[i] = current->allExercise[i]->clone();

	newArr[i] = e->clone();

	for (i=0; i<=size-1; i++)
		delete current->allExercise[i];

	current->allExercise.getArray() = newArr;
}

bool Program:: exerciseNotInProgram (const Exercise & e) 
{
	int i =0 ;

	if (allExercise.getArray() == NULL)
		return true;

	if (this->allExercise.getLogicSize() == 0)
		return true;

	else
	{
		for (i=0; i<this->allExercise.getLogicSize(); i++)
		{
			if (strcmp(allExercise[i]->getDevice()->getName(), e.getDevice()->getName())==0)
				return false;//The Exercise IS IN the program
		}
		return true;
	}
	return true;
}


Exercise* Program:: getExerciseByDeviceName (const char * deviceName)
{
	int i = 0;
	bool flag = false;

	if (allExercise.getArray() == NULL)
		return NULL;

	if (this->allExercise.getLogicSize() == 0)
		return NULL;

	while ((i<this->allExercise.getLogicSize())&&(flag == false))
	{
		if (strcmp(allExercise[i]->getDevice()->getName(),deviceName) == 0)
			flag = true;
		else
			i++;
	}	

	if (flag)
		return (allExercise[i]);
	return NULL;
}

//operator += overload
bool Program:: operator+= (Exercise* e)
{
	if (!((typeid(*e) == typeid(PowerExercise))||(typeid(*e) == typeid(AerobicExercise))))
		return false;
	else
	{
		if (exerciseNotInProgram (*e))
		{
			extandExerciseArray(this,e);
			this->setDate(this->getDate().getToday());
			return true; //succeed
		}

		return false;
	}
}

//operator -= overload
bool Program:: operator-= (Exercise* e)
{
	int i = 0;
	if (this->allExercise.getLogicSize()<=0)
	{
		cout<<"No exercise at all in your program"<<endl;
		return false;
	}
	else
	{
		for (i = 0; i<=this->allExercise.getLogicSize(); i++)
		{
			if ((strcmp(this->allExercise[i]->getDevice()->getName(),e->getDevice()->getName()) == 0)&&(i == this->allExercise.getLogicSize()-1))
			{
				this->allExercise.setLogicSize(this->allExercise.getLogicSize()-1);
				delete this->allExercise[i];
				this->setDate(this->getDate().getToday());
				return true;
			}

			else if ((strcmp(this->allExercise[i]->getDevice()->getName(),e->getDevice()->getName())==0)&&(i != this->allExercise.getLogicSize()-1))
			{
				this->allExercise[i]->setDevice(this->allExercise[this->allExercise.getLogicSize()-1]->getDevice());
				i = this->allExercise.getLogicSize()-1;
				this->allExercise.setLogicSize(this->allExercise.getLogicSize()-1);
				delete this->allExercise[i];
				this->setDate(this->getDate().getToday());
				return true;
			}

			else
			{
				cout<<"No Exercise that associated with the device was found"<<endl;
				return false;
			}
		}
		return false;
	}
	return false;
}

//operator [] overload
Exercise* Program :: operator[] (int index)
{
	if (index<0)
		throw 1;
	else if (index>= this->allExercise.getLogicSize())
		throw 2;
	else
	{
		return (this->allExercise[index]);
	}
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const Program& p)
{
	int i;
	os<<"Your program was last updated at: "<<p.getDate();
	os<<"It has - "<<p.getIndCurr()<<" Exercises."<<endl;

	for (i = 0; i<p.getIndCurr(); i++)
	{
		os<<"exercise "<<i+1<<" info:"<<endl;
		os<<*(p.allExercise[i]);
	}

	return os;
}

void Program:: show () const
{
	cout<<*this;
}

void Program::printSpecificKind(int kind) const
{
	int i;
	int counter = 0;

	if (kind == ALL_EXERCISE)
	{
		cout<<"There are "<<this->allExercise.getLogicSize()<<" Exercise in total in your program"<<endl;
		cout<<"Here are all the exercise in your program:"<< endl;

		for (i=0; i<this->allExercise.getLogicSize(); i++)
			cout<<i+1<<". "<<*(this->allExercise[i]);
	}

	else if (kind == POWER_EXERCISE)
	{
		cout<<"Here are all the POWER EXERCISE in your program :"<<endl;

		for (i=0; i<this->allExercise.getLogicSize(); i++)
		{
			Exercise* e = this->allExercise[i];
			PowerExercise * pe = dynamic_cast<PowerExercise*>(e);
			if (pe!=NULL)
			{
				counter++;
				cout<<counter<<". "<<*(this->allExercise[i]);
			}
		}
		cout<<"Total - "<<counter<<" power exercise in your program"<<endl;
	}

	else if (kind == AEROBIC_EXERCISE)
	{
		cout<<"Here are all the AEROBIC EXERCISE in your program :"<<endl;

		for (i=0; i<this->allExercise.getLogicSize(); i++)
		{
			Exercise* e = this->allExercise[i];
			AerobicExercise * ae = dynamic_cast<AerobicExercise*>(e);
			if (ae != NULL)
			{
				counter++;
				cout<<counter<<". "<<*(this->allExercise[i]);
			}
		}
		cout<<"Total - "<<counter<<" aerobic exercise in your program"<<endl;
	}
	
	else
		cout<<"Illegal input"<<endl;
}



