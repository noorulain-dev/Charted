#pragma once
#include <iostream>
#include <conio.h>
#include "Drake.h"
#include "Enemy.h"

using namespace std;

class Battle 
{
private:
	//attributes
	Drake* fDrake;
	Enemy* fEnemy;
	int fCount;

public:
	//constructor
	Battle();

	//destructor
	virtual ~Battle();

	//overloaded constructor
	Battle(Drake& aDrake_, Enemy& aEnemy_);

	//the fight scene
	string fight();

	//lists the commands
	void warzone();

};