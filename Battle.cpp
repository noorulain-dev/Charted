#include <iostream>
#include "Battle.h"
using namespace std;

// constructor
Battle::Battle() 
{

}

// Destructor
Battle::~Battle() 
{

}

// Overloaded Constructor
Battle::Battle(Drake& drake_, Enemy& enemy_) 
{
	fDrake = &drake_;
	fEnemy = &enemy_;
	fCount = 1;
}

// The fight starts
// The attack is carried out one by one
// Drake and the witch attack alternately
// Damage and health is impacted
// Attack is done when a fighting method is chosen
string Battle::fight() 
{
	string result = "";
	int pressed;
	if (fCount % 2 == 0) {
		cout << " Witch Attacking " << endl;
		cout << "-----------------------" << endl;
		system("pause");

		pressed = (rand() % 3) + 1;
		switch (pressed) {
			//if first option is selected then the damage is returned as a string
			//the setHit function is called and the enemy attacks drake
			//the players attack alternately so the count is increased by one
			//the turn is passed to drake
		case 1:
			fEnemy->setHit(*fDrake);
			result = "Damage: " + to_string(fEnemy->getHit());
			fCount += 1;
			break;
			//if second case is chosen
			//the damage is set to drake's health
			//the value of damage is called from enemy's first skill
		case 2:
			result = fEnemy->setDamage(*fDrake, fEnemy->getSkills(0));
			fCount += 1;
			break;
			//if third case is chosen
			//the damage is set to drake's health
			//the value of damage is called from enemy's second skill
		case 3:
			result = fEnemy->setDamage(*fDrake, fEnemy->getSkills(1));
			fCount += 1;
			break;
			//random number is generated
		default:
			pressed = (rand() % 3) + 1;
			break;
		}
	}
	else 
	{
		//the function is called containing a list of commands
		warzone();
		cout << " Drake's turn " << endl;
		cout << "--------------------------" << endl;
		pressed = _getch();
		switch (pressed) {
			//if first command is chosen
			//the damage is reduced from enemy's health
			//the value of damage is saved in the result string
		case 49:
			fDrake->setHit(*fEnemy);
			result = "Damage: " + to_string(fDrake->getHit());
			fCount += 1;
			break;
		case 50:
			//if second command is chosen
			//the damage will be equal to the first skill's skill damage in the skill list
			//the value of damage is saved in the result string
			result = fDrake->setDamage(*fEnemy, fDrake->getSkills(0));
			fDrake->setStrength(fDrake->getStrength() - 2);
			fCount += 1;
			break;
		case 51:
			//if third command is chosen
			//the damage will be equal to the second skill's skill damage in the skill list
			//the value of damage is saved in the result string
			result = fDrake->setDamage(*fEnemy, fDrake->getSkills(1));
			fDrake->setStrength(fDrake->getStrength() - 1);
			fCount += 1;
			break;
			//if no valid command is chosen
		default:
			result = "Invalid command";
			break;
		}

	}
	return result;
}

// The list of attack methods
void Battle::warzone() 
{
	cout << " Commands " << endl;
	cout << "1. Shoot" << endl;
	cout << "2. Stab" << endl;
	cout << "3. Punch" << endl;
	cout << "--------------------------" << endl;
}