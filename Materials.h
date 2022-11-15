#pragma once
#include <iostream>
#include <string>
using namespace std;
class Materials 
{
private:
	//attributes
	string fName;
	string fDesc;
	bool fMaterialsList;

public:
	//constructor
	Materials();

	//destructor
	~Materials();

	//overloaded constructor
	Materials(string aName, string aDesc);

	//accesors
	//getters and setters
	string getName();

	string getDesc();

	bool getMaterialList();

	//changing the status
	void changeMaterialStatus(bool aStatus);

	//friend operator overload
	friend ostream& operator<< (ostream& aOstream, const Materials& aMaterials);
};