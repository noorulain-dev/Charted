#pragma once
#include <iostream>
#include <string>
#include "Effect.h"

using namespace std;

class Drake;

class Object 
{
private:
	//attributes
	string fName_;
	string fDesc_;
	int fPower_;
	bool fStatus;

public:
	//constructor
	Object();

	//destructor
	~Object();

	//overloaded constructor
	Object(string fName, string aObjectDesc, int aPower);

	//accessors
	//getters and setters
	string getName();

	int getPower();

	bool getStatus();

	void setStatus(bool aStat);

	void effectStatus(Effect& aPower, Drake& aDrake);

	//operator functions
	bool operator== (const Object& aOther) const;
	bool operator!= (const Object& aOther) const;

	//friend operator overload
	friend ostream& operator<< (ostream& aOstream, const Object& aObject);
};