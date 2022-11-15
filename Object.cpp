#include <iostream>
#include "Object.h"
using namespace std;

// Constructor
Object::Object() 
{ 

}

// Destructor
Object::~Object() 
{

}

// Overloaded Constructor=
Object::Object(string name, string description, int power) 
{
	fName_ = name;
	fDesc_ = description;
	fPower_ = power;
	fStatus = false;
}

// Accessors
// Getters and setters

//returns the name of object
string Object::getName() 
{
	return fName_;
}

//returns power of object
int Object::getPower() 
{
	return fPower_;
}

//returns the status of object
bool Object::getStatus() 
{
	return fStatus;
}

//sets the status of object
void Object::setStatus(bool aStatus) 
{
	fStatus = aStatus;
}

//applies the effect to the object by calling the applyEffect function in effect class
void Object::effectStatus(Effect& Effect, Drake& Drake) 
{
	Effect.applyEffect(*this, Drake);
}

// == operator overload
//checks if the current object name is equal to the name of the object sent to function
bool Object::operator==(const Object& obj) const 
{
	if (this->fName_ == obj.fName_) {
		return true;
	}
	else {
		return false;
	}
}

// != operator overload
// checks if the current object is not the same as the passed object
bool Object::operator!=(const Object& obj) const 
{
	return !(*this == obj);
}

//friend operator overload
//prints the name and description of the object
ostream& operator<<(ostream& aOstream, const Object& aObject) 
{
	aOstream << aObject.fName_ << endl;
	aOstream << "Description: " << aObject.fDesc_ << endl;
	return aOstream;
}