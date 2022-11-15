#pragma once
#include <iostream>
using namespace std;
class Object;
class Drake;
class Effect 
{
public:

	//destructor
	virtual ~Effect();

	//applies the effect to the character drake
	virtual void applyEffect(Object& aObj, Drake& aDrake);
};