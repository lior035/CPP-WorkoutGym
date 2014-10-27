#ifndef HC_EXCEPTION
#define HC_EXCEPTION

#include <iostream>
#include <string.h>
#include "healthClub.h"

class HealthClubException
{
	typedef HealthClub::exceptions exceptions;

	char* tName;
	exceptions wrongCode;
	char* msg;

	//private methods to be used only in this sector
	char* setName (const char* name) 
	{
		if (name != NULL)
		{
			//return copy of name
			char* newName = new char [strlen(name)+1];
			strncpy(newName, name,strlen(name));
			newName[strlen(name)] = '\0';

			return newName;
		}
		else
			return NULL;
	}

	void setErrorMsg()
	{
		//set the error msg according  to the error code given
		if (this->wrongCode == HealthClub::REGISTER_FAILED_CLUB_IS_FULL)
			this->msg = this->setName("You exceede the limit of trainers in the club");
		else if (this->wrongCode == HealthClub::REGISTER_FAILED_CANNOT_DUPLICATE_TRAINER)
			this->msg = this->setName("Trainer is already in our club");
		else if (this->wrongCode == HealthClub::INDEX_OUT_OF_BOUNDRIES)
			this->msg = this->setName("The providen index is out of boundries");
	}		

public:
	//constructor
	HealthClubException (char* name, exceptions code)
	{
		//this will build an object of the exception 
		this->wrongCode = code;//Erro code number (enum)
		this->tName = this->setName(name);//The trainer name that the error occurud on him
		this->setErrorMsg();
	}

	//gets
	const char * getName () const //return pointer to copy of trainer name
	{
		return tName;
	}

	int getErrorCode () const //return the error code (as a int)
	{
		return wrongCode;
	}

	const char * getMsg () const //return the error msg
	{
		return msg;
	}

	~HealthClubException()
	{
		delete [] msg;
		delete [] tName;
	}
};

#endif

	

	


