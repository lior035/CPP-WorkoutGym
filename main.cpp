#include <iostream>
#include <fstream>
using namespace std;
#include <cstdlib>
#include <typeinfo.h>
#define Length 20

#include "date.h"
#include "device.h"
#include "trainer.h"
#include "exercise.h"
#include "program.h"
#include "healthClub.h"
#include "aerobicDevice.h"
#include "powerDevice.h"
#include "aerobicExercise.h"
#include "powerExercise.h"
#include "healthClubException.h"

int menuOption ();

void addNewTrainer(HealthClub& club);
	char * inputNameDynamic ();

void addNewDevice(HealthClub& club);

void addExerciseForTrainer (HealthClub& club);

void editExercise (HealthClub & club , int serial);

void removeExercise (HealthClub & club);

void printDevice (HealthClub& clubA);

void printTrainer (HealthClub& clubA);

void printProgram (HealthClub& clubA);

void saveClub (const HealthClub & hc, const char* fileName); //saving the data of the healt club to the file

HealthClub * loadClub (const char * fileName);//reading the data of the file and input it to the health club
	void readClubName (HealthClub * hc, ifstream & inFile);

void main()
{

	char* fileName = "data.bin";

	HealthClub* clubA = loadClub (fileName);

	if (clubA == NULL)
	{
		//reading data from user
		HealthClub clubB ("lior club");
	
		int flag;
		bool end = false;	

		while (end == false)
		{
			flag = menuOption();

			if (flag == 1)
				addNewTrainer(clubB);
			else if (flag == 2)
 				addNewDevice(clubB);
			else if (flag == 3)
				addExerciseForTrainer (clubB);
			else if (flag == 4)
			{
				cout<<"enter serial of device"<<endl;
				int sr;
				cin>>sr;
				editExercise(clubB, sr);
			}
			else if (flag == 5)
				removeExercise (clubB);
			else if (flag == 6)
				printDevice (clubB);
			else if (flag == 7)
			    printTrainer (clubB);
			else if (flag == 8)
				printProgram (clubB);
			else if (flag == 9)
				end = true;
			else 
			{
				cout<<"illegal input retry"<<endl;
				flag = menuOption();
			}
		}
		
		//saving the user data to a file
		saveClub (clubB,fileName);
	}
	
	else
	{
		printTrainer(*clubA);
		printDevice(*clubA);
	}
}

//---------------------------------------------------------------------

int menuOption()
{
	int i;
	cout<<"What do you want to do?"<<endl;
	cout<<"Enter 1 to register a new trainer to this club"<<endl;
	cout<<"Enter 2 to add a device to this club"<<endl;
	cout<<"Enter 3 to add exercise for one of our trainer"<<endl;
	cout<<"Enter 4 to edit exercise of a trainer"<<endl;
	cout<<"Enter 5 to remove exercie of a trainer"<<endl;
	cout<<"Enter 6 to print all the devices in our club"<<endl;
	cout<<"Enter 7 to print all the trainer in our club"<<endl;
	cout<<"Enter 8 to print a specific trainer's program detales"<<endl;
	cout<<"Enter 9 to exit"<<endl;
	cin>>i;
	return i;
}

//---------------------------------------------------------------------

void addNewTrainer(HealthClub& club)
{
	char * tName;

	tName = inputNameDynamic();
	try
	{
		club.addTrainer(tName);
	}
	catch (HealthClubException* bad)
	{
		cout<<"Error code: "<<bad->getErrorCode()<<" - "<<bad->getMsg()<<endl;
		if (bad->getName()!=NULL)
			cout<<bad->getName()<<" was not edded to our club"<<endl;
	}
}

//---------------------------------------------------------------------

char * inputNameDynamic ()
{
	char ch;
	int length = 10;
	int realLength = 0;
	char * helper = new char [length+1];
	char * name = new char[length+1];
	cout<<"Enter name: "<<endl;
	cin.get();
		
	ch = cin.get();
	while (ch != '\n')
	{
		if (realLength == length)
		{
			length*=2;
			delete [] helper;
			helper = new char [length+1];
			name[realLength] = '\0';
			strcpy(helper, name);
			delete [] name;
			name = new char [length+1];
			strcpy (name, helper);
		}

		name[realLength] = ch;
		realLength++;
		ch = cin.get();
	}

	name[realLength] = '\0';
	strcpy(helper, name);
	delete [] name;
	name = new char [realLength+1];
	strcpy (name, helper);
	delete [] helper;
	return name;
}

//------------------------------------------------------

void addNewDevice(HealthClub& club)
{
	char dName [Length];
	char * mName;
	bool isIn = false;
	int i;

	cout<<"Enter the device name (max 20 characters)"<<endl;
	cin.get();
	cin.getline(dName,Length);

	for (i=0; i<club.getTotalDeviceCount(); i++)
	{
		if ((strcmp(club.getDevice(i)->getName(),dName)) == 0)
		{
			isIn = true;
			i = club.getTotalDeviceCount();
		}
	}

	if (isIn)
		cout<<"Device is already in the club"<<endl;
	else
	{
		cout<<"Press 1 if this is an aerobic device, press 2 if this is an power device"<<endl;
		cin>>i;

		while ((i>2)||(i<=0))
		{
			cout<<"Illegal input,  try again"<<endl;
			cin>>i;
		}

		if (i==1)
		{
			cout<<"How much calories this aerobic device burn in hour?"<<endl;
			cin>>i;
			Device* newDevice = new AerobicDevice(i, dName);
			club.addDevice(newDevice);
		}

		else
		{
			cout<<"on which main muscles group this device work on?"<<endl;
			mName = inputNameDynamic();
			Device* newDevice = new PowerDevice(mName, dName);
			club.addDevice(newDevice);
		}
	}
}

//----------------------------------------------------------------------

void addExerciseForTrainer (HealthClub& club)
{
	if (club.getTotalTrainerCount() == 0)
		cout<<"Currently we do not have any trainers, please visit us later"<<endl;
	else if (club.getTotalDeviceCount() == 0)
		cout<<"Currently we do not have any device/exercise, please visit us late"<<endl;

	else
	{
		cout<<"Choose one of our trainers you want to add exercise to: "<<endl;
		
		int i;
		for (i=0; i<club.getTotalTrainerCount(); i++)
			cout<<"Press "<<i+1<<" for "<< club.getTrainer(i)->getName()<<endl;//i always in the boundries

		cin>>i;
		i--;

		try 
		{
			club.getTrainer(i);
		}

		catch (HealthClubException* bad)
		{
			cout<<"Error code : " <<bad->getErrorCode()<<" - " <<bad->getMsg()<<endl;
			cout<<"Try again"<<endl;
			cin>>i;
			i--;
			while ((i<0)|| (i>=club.getTotalTrainerCount()))
			{
				cout<<"Try again"<<endl;
				cout<<"Valid input is 1-"<<club.getTotalTrainerCount()<<endl;
				cin>>i;
				i--;
			}
		}

		Trainer * t = club.getTrainer(i);
	
		if (t->getProgram().getIndCurr() == 0)
			cout<<t->getName()<<" has no exercise at all, you may add any exercise from our club"<<endl;
		else if (t->getProgram().getIndCurr() == club.getTotalDeviceCount())
			cout<<t->getName()<<" has all the exercises that in our club, you cannot add anything"<<endl;
		else
		{
			cout<<t->getName()<<" has those exercise :"<<endl;
			for (i=0; i<t->getProgram().getIndCurr(); i++)
				cout<<i+1<<")"<<(*(t->getProgram().getExercise())[i]);

			cout<<"You may add exercise that does not appear yet in this trainer program and is in our club"<<endl;
		}

		if (t->getProgram().getIndCurr()<club.getTotalDeviceCount())
		{
			cout<<"Here are the exercise in our club: "<<endl;

			for (i =0; i<club.getTotalDeviceCount(); i++)
				cout<<i+1<<") "<<club.getDevice(i)->getName()<<endl;
			
			cout<<endl;
			cout<<"Which of those exercise from above you want to add to "<<t->getName()<<"'s program?"<<endl;
			cin>>i;

			while ((i<1)|| (i>club.getTotalDeviceCount()))
			{
				cout<<"Error, invalid input, try again"<<endl;
				cout<<"Valid input is 1-"<<club.getTotalDeviceCount()<<endl;
				cin>>i;
			}
			i--;

			Exercise * e = new Exercise (club.getDevice(i));

			if (t->getProgram().exerciseNotInProgram(*e) == false)
			{
				cout<<"The exercise you chose to enter is already in, the program remains the same"<<endl;
				delete e;
			}

			else
			{
				delete e;
				Exercise * d;
				int j;
				cout<<"Add this exercise as - 1. aerobic exercise, 2.power exercise"<<endl;
				cin>>j;
				while ((j>2)||(j<=0))
				{
					cout<<"Illegal, try again"<<endl;
					cin>>j;
				}

				if (j ==1)
				{
					cout<<"Enter minutes and heart beat for this exercise"<<endl;
					int hb, min;
					cin>>min>>hb;
					d = new AerobicExercise(club.getDevice(i), min, hb);
				}

				else
				{
					cout<<"Enter the number of sets and rehearsl for this exercise"<<endl;
					int ns, r;
					cin>>ns>>r;
					d = new PowerExercise(club.getDevice(i), ns,r);
				}

				t->getProgram().operator += (d);
			}
		}
	}
}

//-----------------------------------------------------------------------

void editExercise (HealthClub & club , int serial)
{
	if ((serial>=Device::GetSerialNum())||(serial<=999))
		cout<<"illegal serial"<<endl;
	else if (club.getTotalTrainerCount()==0)
		cout<<"No trainer at all"<<endl;
	else
	{
		int i = 0;
		
		Trainer * t;

		cout<<"which trainer you want to edit the exercise?"<<endl;
		
		for(i =0 ; i<club.getTotalTrainerCount(); i++)
			cout<<i+1<<". "<<club.getTrainer(i)->getName()<<endl;		
		cin>>i;
		i--;

		try
		{
			club.getTrainer(i);
		}

		catch (HealthClubException* bad)
		{
			cout<<"Error code : "<<bad->getErrorCode()<<" - "<<bad->getMsg()<<endl;
			cout<<"Try again"<<endl;
			cin>>i;
			i--;
			while ((i<0)||(i>=club.getTotalTrainerCount()))
			{
				cout<<"Try again"<<endl;
				cin>>i;
				i--;
			}
		}

		t = club.getTrainer(i);
		i=0;
		bool end = false;

		while ((i< t->getProgram().getIndCurr())&&(end==false))
		{
			if (t->getProgram().getExercise()[i]->getDevice()->getSerialOfCurr() == serial)
				end = true;
			else
				i++;
		}

		if (end)
		{
			if (typeid(*(t->getProgram().getExercise()[i])) == typeid(AerobicExercise))
			{
				AerobicExercise* p;
				p = (AerobicExercise*) (t->getProgram().getExercise()[i]);
				cout<<"This is aerobic exercise, what do you want to change, 1.minutes, 2.heart beat, 3.both?"<<endl;
				int j;
				cin>>j;

				if (j== 1)
				{
					int min;
					cout<<"new minute: "<<endl;
					cin>>min;
					p->setMinutes(min);
				}
				else if (j==2)
				{
					int hb;
					cout<<"new heart beat:"<<endl;
					cin>>hb;
					p->setHeartBeat(hb);
				}
				else if (j ==3)
				{
					int hb, min;
					cout<<"new minutes and heart beat:"<<endl;
					cin>>min>>hb;
					p->setMinutes(min);
					p->setHeartBeat (hb);
				}
				else 
					cout<<"wrong input"<<endl;
			}

			else //meaning it is a power exercixe
			{
				PowerExercise* p;
				p = (PowerExercise*) (t->getProgram().getExercise()[i]);
				cout<<"This is power exercise, what do you want to change, 1.rehearsals In Set, 2.num of set, 3.both?"<<endl;
				int j;
				cin>>j;

				if (j ==1)
				{
					int rIs;
					cout<<"new num of rehaessl:"<<endl;
					cin>>rIs;
					p->setNumOfRehearsel(rIs);
				}
				else if (j==2 )
				{
					int nOs;
					cout<<"new num of sets:"<<endl;
					cin>>nOs;
					p->setNumOfSets (nOs);
				}
				else if (j==3)
				{
					int nOs, rIs;
					cout<<"new num of sets and num of rehaesrl: "<<endl;
					cin>>nOs>>rIs;
					p->setNumOfSets (nOs);
					p->setNumOfRehearsel(rIs);
				}
				else
					cout<<"wrong input"<<endl;
			}

		}

		else
			cout<<"In this tranier, the exercise is not exiset"<<endl;
	}

}

//----------------------------------------------------------------------

void removeExercise (HealthClub& club)
{
	Trainer* t;
	if (club.getTotalTrainerCount() ==0)
		cout<<"No trainer yet, try later"<<endl;
	else
	{
		int i =0;
		cout<<"Here are our trainer in the club, choose one of them"<<endl;
		
		while (i<club.getTotalTrainerCount())
		{
			cout<<"Press "<<i+1<<") for "<< club.getTrainer(i)->getName()<<endl;
			i++;
		}

		cin>>i;
		i--;

		try 
		{
			club.getTrainer(i);
		}
		catch (HealthClubException * bad)
		{
			cout<<"Error code : "<<bad->getErrorCode()<<" - "<<bad->getMsg()<<endl;
			cout<<"Try again"<<endl;
			cin>>i;
			i--;
			while ((i<0)||(i>=club.getTotalTrainerCount()))
			{
				cout<<"Try again"<<endl;
				cin>>i;
				i--;
			}
		}

		t = club.getTrainer(i);

		if (t->getProgram().getExercise() == NULL)
			cout<<"This trainer has no exercise at all"<<endl;
		else
		{
			cout<<"This trainer's exercises: "<<endl;
			int j =0;
			int k = 0;
			bool end = false;

			while (j<t->getProgram().getIndCurr())
			{
				cout<<(*(*(t->getProgram().getExercise()+j)));
				j++;
			}

			cout<<"Enter serial number of one of the exercise from above"<<endl;;
			cin>>j;

			while ((k<t->getProgram().getIndCurr())&&(end == false))
			{
				if ((*(*(t->getProgram().getExercise()+k))).getDevice()->getSerialOfCurr() == j)
					end = true;
				else
					k++;
			}

			if (end == false)
				cout<<"No such exercise in this trainer program"<<endl;
			else
				t->getProgram().operator -=(*(t->getProgram().getExercise()+k));
	}
	}
}

//----------------------------------------------------------------------

void printDevice (HealthClub& clubA)
{
	int i;
	
	for(i=0; i<clubA.getTotalDeviceCount(); i++)
	{
		cout<<"Device "<<i+1<<endl;
		cout<<(*(clubA.getDevice(i)))<<endl;;
	}
}

//------------------------------------------------------------------------


void printTrainer (HealthClub& clubA)
{
	int i;
	
	for(i=0; i<clubA.getTotalTrainerCount(); i++)
	{
		cout<<"Trainer "<<i+1<<endl;
		cout<<(*(clubA.getTrainer(i)));
	}
}

//-----------------------------------------------------------

void printProgram (HealthClub& clubA)
{
	if (clubA.getTotalTrainerCount() == 0)
		cout<<"No trainer at all in our club at this moment"<<endl;
	else
	{
		cout<<"Choose one of our trainers you want to print his exercise : "<<endl;
		
		int i;
		for (i=0; i<clubA.getTotalTrainerCount(); i++)
			cout<<"Press "<<i+1<<" for "<< clubA.getTrainer(i)->getName()<<endl;

		cin>>i;
		i--;

		try
		{
			clubA.getTrainer(i);
		}

		catch (HealthClubException * bad)
		{
			cout<<"Error : "<<bad->getErrorCode()<<" - "<<bad->getMsg()<<endl;
			cout<<"Try again"<<endl;
			while ((i<0)|| (i>=clubA.getTotalTrainerCount()))
			{
				cout<<"Valid input is 1-"<<clubA.getTotalTrainerCount()<<endl;
				cin>>i;
				i--;
			}
		}

		Trainer * t = clubA.getTrainer(i);
		
		cout<<"What kind of exercise you want to print in that trainer?\n 1.all exercise, 2. power exercise 3. aerobic exercise"<<endl;
		int j;
		cin>>j;

		t->getProgram().printSpecificKind(j-1);
	}
} 

//-----------------------------------------------------------

void saveClub (const HealthClub & hc, const char* fileName)
{
	ofstream outFile (fileName, ios::out|ios::trunc|ios::binary);

	if (outFile.is_open())
	{
		hc.saveToFile(hc, outFile);
		outFile.close();
	}
}

//---------------------------------------------------------------

HealthClub * loadClub (const char * fileName)
{
	//will only open if the file exsists
	ifstream inFile (fileName, ios::in|ios::binary|ios::_Nocreate);

	if (inFile.is_open())
	{
		HealthClub * hc = new HealthClub (inFile);
		inFile.close();
		return hc;
	}

	else
		return NULL;
}
