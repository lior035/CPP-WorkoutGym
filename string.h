#ifndef STRING_H
#define STRING_H

class String
{
	//Private by default
	int length;
	char* str;

public:
	String (char* string = NULL); //Constructor
	String (const String & strToCpy); // Copy constructor

	//gets

	int getLen () const;
	const char * getStr () const;

	//friend function

	friend char * strCopy (int length, char * strSrc);
	friend ostream& operator << (ostream & os ,const String & str); // friend function to overload operator <<
	friend istream& operator >> (istream & is, String & str); // friend function to overload operator >>

	//Operators overloading

	String& operator= (const String & str);//Assign operator overload
	String operator+ (const String & str);//plus operator overload
	bool operator<= (const String & str) const; // <= operator overload
	bool operator> (const String & str) const; // > operator overload (re-usr)
	bool operator == (const String & str) const; // == operator overload 
	bool operator != (const String & str) const; // != operator overload (re-use)
	bool operator< (const String & str) const ;// < operator overload (re-use)
	bool operator>= (const String & str) const; // >= operator overload (re-use)
	char operator [] (int index) const; // [] operator overload
	char& operator [] (int index); // [] operator overload 
	operator char* ()const; // casting operator
	
	~String();// destructor;
};

#endif 