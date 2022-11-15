#pragma once
#include <iostream>
#include <string>

using namespace std;

struct SkillSet 
{
	//Attributes
	string fName_;
	int HP;

	//Constructor
	SkillSet();

	//Destructor
	~SkillSet();

	//Overloaded constructor
	SkillSet(string name, int hp);

};
