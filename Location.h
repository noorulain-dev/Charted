#pragma once
#include <iostream>
#include "Materials.h"

using namespace std;

class Battle;

class Location 
{
private:
	//attributes
	Materials fMaterialsList[4];
	bool fPermission;

public:

	//Default Constructor
	Location();

	//Destructor
	~Location();

	//Overloaded Constructor
	Location(Materials list[4], bool permission);

	// calls the fight function to start the fight
	string startFight(Battle& battle);

	//accessors
	//getters and setters
	bool getAccess();

	void setAccess(bool aAccess);

	string getMaterialsDesc(int i);
};