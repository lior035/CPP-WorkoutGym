#include <iostream>
using namespace std;

#include "trainer.h"
#include "date.h"

#include <string.h>

Trainer:: Trainer (char * name) //constructor
{
	if (name == NULL)
		this->name = NULL;
	else
	{
		this->name = new char [strlen(name)+1];
		strcpy(this->name,name);
	}
}

Trainer:: Trainer(ifstream & inFile)//constructor by file
{
	//this constructor will initialize only the trainer name without his program 
	//assumption - the file is open in the coorect place

	int length;
	inFile.read((char*)&length,sizeof(int));//reading the length of this trainer name from the file
	//allocating and reading the name of the trainer from the file
	this->name = new char [length+1];
	inFile.read ((char*)this->name, length);
	this->name[length] = '\0';
}

Trainer:: Trainer (Trainer & tToCopy): trainerProgram(tToCopy.getProgram())//Copy constructor
{
	int length;
	
	if(tToCopy.name ==	NULL)
			this->name = NULL;
	else
	{
		length = strlen(tToCopy.getName());
		this->name = new char [length+1];
		strcpy(this->name,tToCopy.getName());
	}
}

 //sets

void Trainer:: setName (char* name)
{
	int length;
	int realLength;

	if (this->name==NULL)
	{
		if (name != NULL)
		{
			realLength = strlen(name);
			this->name = new char [realLength+1];
			strcpy(this->name,name);
		}

		else
		{
			char ch;
			length = 10;
			realLength = 0;
			char * helper = new char [length+1];
			this->name = new char[length+1];
			cout<<"Enter trainer name: "<<endl;
		
			ch = cin.get();
			while (ch != '\n')
			{
				if (realLength == length)
				{
					length*=2;
					delete [] helper;
					helper = new char [length+1];
					this->name[realLength] = '\0';
					strcpy(helper, this->name);
					delete [] this->name;
					this->name = new char [length+1];
					strcpy (this->name, helper);
				}

				this->name[realLength] = ch;
				realLength++;
				ch = cin.get();
			}
			this->name[realLength] = '\0';
			strcpy(helper, this->name);
			delete [] this->name;
			this->name = new char [realLength+1];
			strcpy (this->name, helper);
			delete [] helper;
		}
	}

	else
		cout<<"There is a name already"<<endl;
}

void Trainer:: setProgram (const Program & p)
{
	trainerProgram = p;
}

void Trainer:: setProgram ()
{
	Date d;
	trainerProgram.setDate(d.getToday());
}
	
//gets

char * Trainer:: getName () const
{
	return name;
}

Program& Trainer:: getProgram() 
{
	return trainerProgram;
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const Trainer& t)
{
	os<<"Trainer name: "<<t.getName()<<endl;
	return os;
}

void Trainer::show() const 
{
	cout<<*this; //re-use
}

Trainer:: ~Trainer ()//destractor
{
	if (name != NULL)
		delete []name;
}


