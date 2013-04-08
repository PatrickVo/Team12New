
#pragma once

#include "Utility.h"

#include <string>

using namespace std;

class DBDLL_API Attribute
{
private:
	string type;

public:
	// default constructor
	Attribute ();

	// constructor
	Attribute (string newType);

	// destructor
	~Attribute ();

	// sets what type the attribute is
	int setType (string newType);

	// gets the attribute type
	string getType ();

	// overloaded equality operator
	bool operator== (const Attribute compare) const;

private:
	bool checkNewType (string newType);
};