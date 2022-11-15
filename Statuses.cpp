#include <iostream>
#include "Statuses.h"
using namespace std;

// Constructor
Statuses::Statuses() 
{ 

}


// Destructor
Statuses::~Statuses() 
{ 

}

// Overloaded constructor
Statuses::Statuses(string type_, int size_) 
{
	fType = type_;
	fSize = size_;
	fStatus = false;
}

// updates the effect on Drake and returns a string containing his condition as well
void Statuses::affectDrake(Drake& drake) 
{
	if (fStatus == true) 
	{
		if (fType == "Blood loss") 
		{
			cout << "Bleeding until bandaged" << endl;
			drake.setHP(drake.getHP() - fSize);
		}
		else if (fType == "Screaming Noises") 
		{
			cout << "It's too loud!!!" << endl;
			drake.setConclusions(false);
		}
	}
}

//Accessors
//Getters and Setters
bool Statuses::getStatus() 
{
	return fStatus;
}

//sets the status of node
void Statuses::setStatus(bool stat) 
{
	fStatus = stat;
}

//returns the type of node
string Statuses::getType() 
{
	return fType;
}

//returns the size of node
int Statuses::getSize() 
{
	return fSize;
}

//switches the status
// if status is true then it will be false, and vise versa
void Statuses::StatusChange() 
{
	if (fStatus == true)
	{
		fStatus = false;
	}
	else 
	{
		fStatus = true;
	}
}
