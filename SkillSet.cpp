#include <iostream>
#include "SkillSet.h"
using namespace std;

// Default Constructor
SkillSet::SkillSet() 
{ 

}

// Destructor
SkillSet::~SkillSet() 
{

}

// Overloaded Constructor
SkillSet::SkillSet(string name, int damage) 
{
	fName_ = name;
	HP = damage;
}