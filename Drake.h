#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "SkillSet.h"
#include "Person.h"
#include "Location.h"
#include "DoublyLinkedNode.h"
#include "DoublyLinkedList.h"
#include "Object.h"
#include "Enemy.h"
#include "Itr.h"

using namespace std;

class Drake : public Person 
{
public:
	//a type is defined to shorten it for later use
	typedef DoublyLinkedNode<Object>::Node Collection;

private:
	//attributes
	int fStrength_;
	Object fCarrying;
	bool fSeeing;
	Collection fCollection;
	bool fCheckStrength;
	bool fCheckStatus;

public:
	//constructor
	Drake();

	// destructor
	virtual ~Drake();

	//overloaded constructor
	Drake(int aHP, vector<SkillSet> aSkillSet, int aHitDamage, int aEnergy);

	// accessors
	// getters and setters
	int getStrength();

	void setStrength(int aEnergy);

	void showCollection(Iterator<Object>& iterator);

	void addObject(Object& object);

	void throwObject(Collection& object);

	DoublyLinkedNode<Object>& getFirstObject();

	Object& objectCarrying();

	void setHit(Person& person) override;

	bool getConclusions();

	void setConclusions(bool observation);

	bool getIfStrength();

	void setIfStrength(bool energy);

	bool getStatus();

	void setStatus(bool aAlive);

	bool checkObject(Iterator<Object>& itr, Object& object);

};