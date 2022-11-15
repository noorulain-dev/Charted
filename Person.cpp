#include <iostream>
#include "Person.h"

using namespace std;

// Constructor
Person::Person() 
{ 

}

// Destructor
Person::~Person() { 

}

// Overloaded Constructor
Person::Person(int points_, vector<SkillSet> skills_, int damage_) 
{
	fPoints = points_;
	fSkills = skills_;
	fHit = damage_;
}


//Accesors
//Getters and Setters

//returns the current health
int Person::getHP() 
{
	return fPoints;
}

//sets the current health
void Person::setHP(int points_) 
{
	fPoints = points_;
}

//returns the skill from the skills array
SkillSet& Person::getSkills(int skillSet) 
{
	return fSkills[skillSet];
}

//sets the skill in the skills array
void Person::setSkills(SkillSet skillSet) 
{
	fSkills.push_back(skillSet);
}

//returns if hit
int Person::getHit() 
{
	return fHit;
}

//function to be overriden
//sets if hit
void Person::setHit(Person& person) 
{ 

}

//set the damage of of the person
string Person::setDamage(Person& enemy, SkillSet skillSet) 
{
	string returnedString = "";
	//if the enemy hit equals to 5 then the updated health of the enemy will equal to the current health deducted by the damage induced
	//and a string containing the name and damage is returned
	//this is set as a string initialised as returnString
	if (enemy.getHit() == 5)
	{
		enemy.setHP(enemy.getHP() - skillSet.HP);
		string returnedString = "Name:" + skillSet.fName_ + "\nHit points: " + to_string(skillSet.HP);
	}
	//if the enemy hit equals to 15 then the damage is received from the skillset array
	//the hit is set as the hit induced by enemy and a string is returned containing the name and damage caused by enemy 
	//saved in the returnedString string variable
	else if (enemy.getHit() == 15)
	{
		this->fHit = skillSet.HP;
		this->setHit(enemy);
		this->fHit = 5;
		returnedString = "Name: " + skillSet.fName_ + "\nHit points: " + to_string(skillSet.HP);
	}

	return returnedString;
}