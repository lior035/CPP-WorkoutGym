#include <iostream>
using namespace std;

#include "date.h"

bool Date::legalMonth (int m) const
{
	if ((m>12) || (m<1))
		return false;
	return true;
}

bool Date::legalDay (int d) const
{
	if ((d>31) || (d<1))
		return false;
	return true;
}


Date:: Date (int day, int month, int year)
{
	this->day = day;
	this->month=month;
	this ->year = year;
}

//sets

bool Date:: setDay (int day)
{
	if (legalDay(day))
	{
		this->day = day;
		return true;
	}

	else 
	{
		cout<<"illegal day"<<endl;
		return false;
	}
}

bool Date:: setMonth (int month)
{
	if (legalMonth(month))
	{
		this->month = month;
		return true;
	}

	else
	{
		cout<<"illegal monthe"<<endl;
		return false;
	}
}

void Date:: setYear (int year)
{
	this->year = year;
}

//gets

int Date::  getDay() const
{
	return day;
}

int Date::  getMonth()const
{
	return month;
}

int Date:: getYear() const
{
	return year;
}

Date Date:: getToday() const
{
	time_t t = time(0);
	tm* lt = localtime(&t);
	
	Date today;
	today.setDay(lt->tm_mday);
	today.setMonth(lt->tm_mon+1);
	today.setYear(lt->tm_year+1900);
	
	return today;
}

//operator << overload by friend function
ostream& operator<< (ostream & os, const Date& d)
{
	os<<d.getDay()<<'.'<<d.getMonth()<<'.'<<d.getYear()<<endl;
	return os;
}

void Date:: show (char separator) const 
{
	//cout<<day<<separator<<month<<separator<<year<<endl; -> remove the // if you want to enable the separator featur
	cout<<*this;
}
