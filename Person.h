#pragma once
#include <iostream>
#include <vector>
#include "SkillSet.h"

using namespace std;

class Person 
{
private:
	//Attributes
	int fPoints;
	vector<SkillSet> fSkills;
	int fHit;

public:
	//Constructor
	Person();

	//Destructir
	virtual ~Person();

	//Overloaded Constructor
	Person(int aPoints_, vector<SkillSet> aSkills_, int aDamage_);

	//Accessors
	//Getters and Setters
	int getHP();

	void setHP(int aPoints);

	SkillSet& getSkills(int aSkills);

	void setSkills(SkillSet aSkillSet);

	int getHit();

	virtual void setHit(Person& aPerson);

	string setDamage(Person& aPerson, SkillSet aSkillSet);

};
