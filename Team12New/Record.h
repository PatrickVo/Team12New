
#pragma once

#include "Utility.h"

#include <string>
#include <vector>

using namespace std;

class DBDLL_API Record
{
private:
	vector<string> entries;

public:
	// default constructor
	Record ();

	// constructor
	Record (vector<string> newEntries);

	// destructor
	~Record ();

	// retrieve entry based on position
	string getEntry (int position);

	// modify an entry
	int setEntry (int position, string entry);

	// add an entry
	int addEntry (string entry);

	// remove an entry at the index
	int deleteEntry (int position);

	// returns the size of the Record
	int getSize ();
};