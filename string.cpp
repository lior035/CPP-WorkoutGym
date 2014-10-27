#include <iostream>
using namespace std;

#include "string.h"

String ::String(char * str) //Constructor
{
	int i = 0;
	
	if (str != NULL)
	{
		while (str[i]!= '\0')
			i++;
	}

	this->length = i;
	this->str = strCopy (this->length, str);
}

String:: String (const String & strToCpy): str(NULL)
{
	(*this) = strToCpy; // re-use the operator = we overload
}

//gets

int String:: getLen() const
{
	return length;
}

const char * String:: getStr () const
{
	return str;
}

//friend function

char * strCopy (int length, char * strSrc)
{
	char * temp;

	if (length ==0)
		return NULL;

	else
	{
		int j = 0;
		temp = new char [length+1];

		for (j=0; j<length; j++)
			temp[j] = strSrc[j];
		temp[j] = '\0';
		
		return temp;
	}
}

ostream& operator << (ostream & os ,const String & str) // friend function to overload operator <<
{
	os<<str.str;
	return os;
}

istream& operator >> (istream & is, String & str) // friend function to overload operator >>
{

	if (str.str != NULL)
		delete [] str.str;

	cout<<"Please insert a string with maximum "<<str.length<<" chars"<<endl;

	is.getline(str.str,str.length,'\n');
	return is;
}

//Operators overloading

String& String::operator =(const String & str) // assign operator overload
{
	if (this!= &str)
	{
		delete [] this->str; 
		this->length = str.length;
		this->str = strCopy (str.length, str.str);
		return *this;
	}
	return *this;
}

String String:: operator+ (const String & str) //+ operator overload
{
	String temp;
	int len = str.length + this->length;

	temp.str = new char [len+1];
	temp.length = len;
	int i;

	for (i=0; i<this->length; i++)
		temp[i] = (*this)[i];
	for (; i<len; i++)
		temp[i] = str[i-this->length];
	temp[i] = '\0';

	return temp;
}

bool String:: operator<= (const String & str) const // <= operator overload
{
	int i, j;
	
	i =0;
	j = 0;

	while (((*this)[i] != '\0')&&(str[j] !='\0'))
	{
		if ((*this)[i] - 'A' < str[j]-'A')
			return true;
		else if ((*this)[i] - 'A' > str[j]-'A')
			return false;
		else
		{
			i++;
			j++;
		}
	}

	if ((*this)[i] == '\0')
		return true;
	else
		return false;
}


bool String:: operator> (const String & str) const // > operator overload (re-usr)
{
	return !((*this)<=str);
}

char String:: operator [] (int index) const // [] operator overload 
{
	if (index<0 || index>this->length)
		throw 'e';
	else
		return this->str[index];
}

bool String:: operator == (const String & str) const // == operator overload 
{
	int i, j;
	
	i =0;
	j = 0;

	if (this->length != str.length)
		return false;

	else
	{
		while (((*this)[i] != '\0')&&(str[j] !='\0'))
		{
			if ((*this)[i] != str[j])
				return false;
			else
			{
				i++;
				j++;
			}
		}
		return true;
	}
}

bool String:: operator != (const String & str) const // != operator overload (re-use)
{
	return !((*this)==str);
}

bool String:: operator< (const String & str) const // < operator overload (re-use)
{
	return (((*this)<=str)&&((*this)!=str));
}

bool String:: operator>= (const String & str) const // >= operator overload (re-use)
{
	return !((*this)<str);
}

char& String:: operator [] (int index) // [] operator overload 
{
	if (index<0 || index>this->length)
		throw 'e';
	else
		return this->str[index];
}

String :: operator char* ()const // casting operator
{
	char * temp;
	temp = strCopy(this->length,this->str);
	return temp;
}

String::~String() 
{
	delete [] this->str;
}