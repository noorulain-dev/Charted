#include <iostream>
#include "Enemy.h"
using namespace std;

// Default constructor
Enemy::Enemy() 
{ 

}

// Destructor
Enemy::~Enemy() 
{ 

}

// Overloaded constructor
Enemy::Enemy(int aHP, vector<SkillSet> skillSet, int damage, int healer) : Person(aHP, skillSet, damage) 
{
	fHeal = healer;
}

//Acessors
//Getters and setters
int Enemy::getHeal() 
{
	return fHeal;
}

void Enemy::setHeal(int healing) 
{
	fHeal = healing;
}

void Enemy::setHit(Person& person)
{
	if (person.getHP() > 0) {
		person.setHP(person.getHP() - this->getHit());
	}
}