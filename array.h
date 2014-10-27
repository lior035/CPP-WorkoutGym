#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class Array
{
	//private by defualt:
	int phyisicSize, logicSize;
	T** arr; // array of pointers to type T

	//private function member for Array<t>
	void reAlocate(T** arr);
	void deepCopy(int place, T** arr, T* newItem);

public:
	Array (int size = 0); //Constructor

	//operators overload
	Array& operator+= (T* newItem); //operator += overload
    T* operator[](int index) const; //operator [] overload
	Array& operator-= (int index); //operator -= overload (remove by index)

	void replaceCell (int index,T* rep);

	~Array();

	//gets
	int getLogicSize ()const
	{
		return logicSize;
	}

	int getPhyisicSize() const
	{
		return phyisicSize;
	}

	T**& getArray()
	{
		return arr;
	}

	//sets - use curfully
	void setLogicSize(int size)
	{
		logicSize = size;
	}
};

//constructor
template <class T>
Array<T>::Array(int size)
{
	if (size<0)
		throw "illegal size";
	else if (size ==0)
	{
		phyisicSize = 2;
		logicSize=0;
		arr = new T* [phyisicSize];
	}

	else
	{
		phyisicSize = 2*size;
		logicSize = size;
		arr = new T* [phyisicSize];
	}
}

//operator += overload
template <class T>
Array<T>& Array<T>::operator +=(T *newItem)
{
	if (phyisicSize == logicSize)
		arr = this->reAlocate(arr);//re alocating the array

	this->deepCopy(logicSize, arr, newItem) //will copy to arr in place logicSize the newItem
	logicSize++;

	return *this;
}

//sub functions for operator+=

template <class T> 
void Array<T>::reAlocate(T **arr)
{
	//this function will copy in a deep way all the current array to new allocated array (twice the size)
	int i;
	this->phyisicSize *=2;

	T** newArr = new T* [this->getPhyisicSize()];

	//copy each cell of the previous array to the new array in a deep level
	for (i=0; i<logicSize; i++)
	{
		T* current = this->arr[i];
		this->deepCopy(i, newArr, current);
	}

	if (this->arr != NULL)
	{
		//deleting the previous array
		for (i = 0; i<logicSize; i++)
		{
		 //requirment:: T must has destructor
			delete this->arr[i];
		}
		delete [] this->arr;
	}

	this->arr = newArr;
}

template <class T>
void Array<T>::deepCopy(int place, T** arr, T* newItem)
{
	//requirment:: T must has copy constructor (which preform deep level copy)
	T* item = new T(newItem);
	arr[place] = item;
}

//operator [] overload
template <class T>
T* Array<T>:: operator[](int index) const
{
	//will return the pointer in the index position
	if (this->getLogicSize()==0)
		return this->arr[index];

	if ((index>=this->getLogicSize()) || (index<0))
		throw "Out of boundries"; 
	else
		return this->arr[index];
}

//remove a member from the array using the operator -= overload
template <class T>
Array<T>& Array<T>:: operator-= (int index)
{
	if ((index<0)||(index>=this->getLogicSize()))
		throw "Out of boundries";
	else
	{
		T* toRemove = this->arr[index];
		int i;

		for (i = index; i<phyisicSize-1; i++)
			arr[i] = arr[i+1];

		delete toRemove;
		delete arr[phyisicSize-1];
		phyisicSize--;
		logicSize--;
	}
	return *this;
}

template<class T>
void Array<T>::replaceCell(int i, T* rep)
{
	if ((i<0)||(i>=logicSize))
		throw "out of boundries";
	else
		this->arr[i] = rep;
	
}

//destructor
template <class T>
Array<T>::~Array()
{
	int i;
	for (i=0; i<logicSize; i++)
	{
		if (arr[i] != NULL)
			delete arr[i];
	}
	delete [] arr;
}
#endif