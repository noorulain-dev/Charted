#include <iostream>
#include "Materials.h"

using namespace std;

// Contructor
Materials::Materials() 
{ 

}

// Destructor
Materials::~Materials() 
{ 

}

// Overloaded constructor
Materials::Materials(string name_, string desc_) 
{
	fName = name_;
	fDesc = desc_;
}

//Accessors
//Getters and setters


//returns the name of the material
string Materials::getName() 
{
	return fName;
}

//returns description of the material
string Materials::getDesc() 
{
	return fDesc;
}

//returns if the material list has any materials
bool Materials::getMaterialList() 
{
	return fMaterialsList;
}

// Changing the status
void Materials::changeMaterialStatus(bool status) 
{
	fMaterialsList = status;
}

// Friend operator overload
ostream& operator<<(ostream& aOstream, const Materials& aMaterials) 
{
	aOstream << aMaterials.fName;
	return aOstream;
}