#pragma once
#include <iostream>
#include <vector>
#include "SkillSet.h"
#include "Person.h"
using namespace std;
class Enemy : public Person 
{
private:
	//attribute
	int fHeal;

public:
	//constructor
	Enemy();

	//destructor
	virtual ~Enemy();

	//overload constructor
	Enemy(int aHP, vector<SkillSet> skillSet, int damage, int healer);

	//accessors
	//getters and setters
	int getHeal();

	void setHeal(int healing);

	void setHit(Person& person) override;

};