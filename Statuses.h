#pragma once
#include <iostream>
#include <string>
#include "Drake.h"
using namespace std;
class Statuses 
{
private:
	//Attributes
	bool fStatus;
	string fType;
	int fSize;

public:
	//constructor
	Statuses();

	//destrucctor
	~Statuses();

	//overloaded constructor
	Statuses(string aType_, int aSize_);

	// updates the effect on Drake and returns a string containing his condition as well
	void affectDrake(Drake& aDrake);

	//Accessors
	//Getters and setters
	void setStatus(bool aStat);

	bool getStatus();

	string getType();

	int getSize();

	//toggles the status
	void StatusChange();
};