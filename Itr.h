#pragma once
#include <iostream>
#include <string>

using namespace std;

//this is a template class
template<class Info>

class Iterator 
{

public:
	//constructor
	Iterator() {

	}

	//following are all pure virtual functions
	//Destructor
	virtual ~Iterator() {

	}

	//operator overload
	virtual Info operator*() = 0;

	// ++ operator overload
	virtual Iterator<Info>& operator++() = 0;

	// ++ operator overload
	virtual Iterator<Info>& operator++(int) = 0;

	// -- operator overload
	virtual Iterator<Info>& operator--() = 0;

	// -- operator overload
	virtual Iterator<Info>& operator--(int) = 0;

	// == operator overload
	virtual bool operator== (Iterator<Info>& aOther) = 0;

	// != Operator overload
	bool operator!= (Iterator<Info>& aOther) 
	{
		return !(*this == aOther);
	}

	// start of the array
	virtual Iterator<Info>& begin() = 0;

	/// end of the array
	virtual Iterator<Info>& end() const = 0;

};