#ifndef TRAINER_H
#define TRAINER_H

#include "program.h"
#include <fstream>

class Trainer
{
	//private by defult
	 char * name;
	 Program trainerProgram;
	 Trainer& operator= (const Trainer& t) {}; // Private operator overload for =; we don't allow to do t1=t2

public:
	Trainer (char * name = NULL); //constructor
	Trainer (ifstream & inFile); // constructor by file
	Trainer (Trainer & tToCopy);//Copy constructor

	//sets

	void setName (char* name = NULL);
	void setProgram (const Program & p);
	void setProgram ();
	
	//gets

    char * getName () const;
	Program& getProgram() ;
	
    //operator << overload by friend function
	friend ostream& operator<< (ostream & os, const Trainer& t);

	void show () const;

	~Trainer (); //destractor	
};

#endif //TRAINER_H

