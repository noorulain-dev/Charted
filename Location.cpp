#include <iostream>
#include "Location.h"
#include "Battle.h"

using namespace std;

// Default Constructor
Location::Location() {

}

// Destructor
Location::~Location() {

}

// Overloaded Constructor
Location::Location(Materials list[4], bool permiss) 
{
	for (int i = 0; i < 4; i++) {
		fMaterialsList[i] = list[i];
	}
	fPermission = permiss;
}

// calls the fight function to start the fight
string Location::startFight(Battle& battle) 
{
	return battle.fight();
}

// Accessors
// Getters and setters

//returns if drake has permission to access that location
bool Location::getAccess() 
{
	return fPermission;
}

//sets if drake has permission to acccess that location
void Location::setAccess(bool permiss) 
{
	fPermission = permiss;
}

//returns a string of description of the targeted material
string Location::getMaterialsDesc(int i) 
{
	return fMaterialsList[i].getDesc();
}
