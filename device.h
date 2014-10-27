#ifndef DEVICE_H
#define DEVICE_H
#define TOTALLENGTH 20

#include <fstream>
//=====================================ABSTRACT CLASS!!!!!======================================
class Device
{
	//protcted  for inheritance use
protected:
	char name [TOTALLENGTH+1];
	int serialNum;
	static int SerialNumber;

	virtual void addToPrint (ostream& os) const {};

public:
	Device (const char * name = NULL);//constructor
	Device (ifstream & inFile); //constructor by file

	//sets
	void setName ();
	void setName (const char * name);
	void cpyName (const char* name);
	void setSerialOfCurr(int newSer);
	static void SetSerialNum (int offset, char pos);
	static void SetSerialNum (int newSerial);

	
	//gets
	const char * getName () const;
	int getSerialOfCurr () const;
	static int GetSerialNum ();

	//operators overload 

	bool operator== (const Device & d) const //operator == overload
	{
		return (this->getSerialOfCurr()==d.getSerialOfCurr());
	}

	//operator << overload by friend function
	friend ostream& operator<< (ostream & os, const Device& d);
	//operator >> overload by friend function
	friend istream& operator>> (istream & is, const Device& d);

	//those virtuals to be used by the sons
	virtual void showSafetyInstructions () const = 0;
	virtual Device* clone () const =0;

	virtual void saveDeviceToFile (ofstream & outFile) const;
	
	void show () const;
	virtual ~Device()
	{
	}
};

#endif //DEVICE_H

