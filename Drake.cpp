#include <iostream>
#include "Drake.h"

using namespace std;

// Default Constructor
Drake::Drake() 
{

}

// Destructor
Drake::~Drake() 
{ 

}

// Overloaded Constructor
Drake::Drake(int points_, vector<SkillSet> skills, int damage, int strength) : Person(points_, skills, damage)
{
	fStrength_ = points_;
	fSeeing = true;
	fCheckStrength = true;
	fCheckStatus = true;
}

// Acessors
// Getters and Setters

//returns the strength
int Drake::getStrength() 
{
	return fStrength_;
}

//returns the object carried by drake
Object& Drake::objectCarrying() 
{
	return fCarrying;
}

// sets the strength of drake
void Drake::setStrength(int strength_) 
{
	strength_ = strength_;
}

//returns if drake can see
bool Drake::getConclusions() 
{
	return fSeeing;
}

//sets if drake can see
void Drake::setConclusions(bool conclusion) 
{
	fSeeing = conclusion;
}

//returns if the drake has strength
bool Drake::getIfStrength() 
{
	return fCheckStrength;
}

//sets if drake has strength
void Drake::setIfStrength(bool strength_) 
{
	fCheckStrength = strength_;
}

//returns if drake is alive
bool Drake::getStatus() 
{
	return fCheckStatus;
}

//sets if drake is alive
void Drake::setStatus(bool status) 
{
	fCheckStatus = status;
}

//shows collection
void Drake::showCollection(Iterator<Object>& itr) 
{
	//pointer pointing to first node in the collection when the function is called
	Collection* ptr = &(fCollection.getFirstNode());
	DoublyLinkedList<Object>* lDoublyPtr = dynamic_cast<DoublyLinkedList<Object>*>(&itr);
	//setting collectionOpened to be true
	bool collectionOpened = true;
	//initialising an integer for the time the key has been pressed by the user
	int pressed;
	//if the node that the pointer is pointing to returns an empty string name then the following msg is displayed
	if (ptr->getValue().getName() == "") 
	{
		cout << "Collection is empty" << endl;
	}
	else
	{
		//else the collection is displayed
		system("cls");
		while (collectionOpened == true) 
		{
			cout << " COLLECTION " << endl;
			cout << *itr << endl;
			//view previous object
			cout << "1. Previous Object" << endl;
			//view next object
			cout << "2. Next Object" << endl;
			//use the object
			cout << "3. Use Object" << endl;
			//close the collection
			cout << "0. Close Collection" << endl;
			//gets the key pressed by the user
			pressed = _getch();
			switch (pressed) 
			{
				//if first option is selected
			case 49:
				system("cls");
				//if the user clicks previous option and reaches the first object in the collection then the following message is displayed
				if (itr == itr.begin()) 
				{
					cout << "You have reached the beginning of the list" << endl;
				}
				else if (itr != itr.begin()) 
				{
					itr--;
				}
				break;
				//if second option is selected
			case 50:
				//if the user clicks next and the end of the list is reached then the following messsage will be displayed
				if (itr == itr.end()) 
				{
					system("cls");
					cout << "End of list" <<
						endl;
				}
				else if (itr != itr.end()) 
				{
					system("cls");
					itr++;
				}
				break;
				//if third option is selected
			case 51:
				//when user chooses the option to use the object, then the iterator pointer points to that object it is saved in the fCarrying variable
				//the collection is closed
				fCarrying = *itr;
				system("cls");
				collectionOpened = false;
				break;
				//if fourth option is selected
			case 48:
				//if the user chooses to close the collection then the loop is set to false and the collection is closed. 
				system("cls");
				collectionOpened = false;
				break;
				//if no options are selected
			default:
				system("cls");
				cout << "Invalid Command" <<
					endl;
			}
		}
	}
}

//remove an object from the collection
void Drake::throwObject(Collection& Obj) 
{
	Obj.remove();
}

// adds an object to the collection
void Drake::addObject(Object& newObj) 
{
	//the newNode pointer points to the new object to be added in the collection
	Collection* newNode = new Collection(newObj);
	//if the collection is empty then the this pointer is set as the first object in the collection
	if (fCollection.getFirstNode().getValue().getName() == "") 
	{
		fCollection.setFirstNode(*newNode);
	}
	else 
	{
		//else it is appended at the end of the list as the last node
		fCollection.getEndNode().append(*newNode);
	}
}

// Starts the collection from the first object
DoublyLinkedNode<Object>& Drake::getFirstObject() 
{
	return fCollection.getFirstNode();
}

// Attacks the enemy
void Drake::setHit(Person& person) 
{
	Enemy* enemy = dynamic_cast<Enemy*>(&person);
	//if the enemy's healing is now zero, then the attack damage is reduced from enemy's total health
	if (enemy->getHeal() <= 0) 
	{
		enemy->setHP(enemy->getHP() - this->getHit());
	}
	// if the enemy's healing ability is still present but removing it from the attack damage will reduce to greater or equal to zero
	// then the healing ability left will be the currently healing ability deducted by the attack damage
	else if (enemy->getHeal() - this->getHit() >= 0) 
	{
		enemy->setHeal(enemy->getHeal() - this->getHit());
	}
	//if the healing ability will become less than zero upon attack
	//then the healing ability is set to zero
	//the final health will be set as enemy's current health after deducting attack damage and healing ability
	else if (enemy->getHeal() - this->getHit() < 0) 
	{
		enemy->setHeal(0);
		int remainder = abs(enemy->getHeal() - this->getHit());
		enemy->setHP(enemy->getHP() - remainder);
	}
}

// it finds the object in the iterator array by looping through it
bool Drake::checkObject(Iterator<Object>& itr, Object& obj) 
{
	while (itr != itr.end()) 
	{
		if (*itr == obj) 
		{
			return true;
		}
		itr++;
	}
	if (itr == itr.end()) 
	{
		if (*itr == obj) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	while (itr != itr.begin()) 
	{
		itr--;
	}
}