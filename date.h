#ifndef DATE_H
#define DATE_H
#include <time.h>

class Date
{
	//private by defult
	int day ;
	int month;
	int year;
	bool legalDay (int d) const; //private method
	bool legalMonth (int m) const ; //private method

public:
	Date (int day =1 , int month = 1 , int year = 1); //constructor

	//sets
	bool setDay (int day);
	bool setMonth (int month);
	void setYear (int year);

	//gets
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	Date getToday() const;

	//operator << overload by friend function
	friend ostream& operator<< (ostream & os, const Date& d);
	
	void show (char separator = '/') const;
};

#endif //DATE_H

