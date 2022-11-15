#include <iostream>
#include "Effect.h"
#include "Drake.h"
using namespace std;

// Destructor
Effect::~Effect() 
{ 

}

// Adds effect to the drakes character
void Effect::applyEffect(Object& obj, Drake& drake) 
{
	drake.setHP(drake.getHP() + obj.getPower());
}