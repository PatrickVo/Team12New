
#pragma once

#include "Attribute.h"
#include "Record.h"

#include <vector>
#include <utility>
#include <string>

using namespace std;

class DBDLL_API Table
{
private:
	vector<Record> records;
	vector<pair<string, Attribute>> columns;

public:

	// default constructor
	Table ();

	// constructor that takes a list of names and attributes
	Table (vector<pair<string, Attribute>> namesAndAttributes);

	// destructor
	~Table ();

	// add a column
	int addColumn (string name, Attribute type);

	// delete a column
	int deleteColumn (string name);

	// insert a record
	int insertRecord (Record newRecord);

	// delete a record
	int deleteRecord (int position);

	// returns a list of the attributes of the table
	vector<pair<string, Attribute>> getAttributes ();
	vector<pair<string, Attribute>> getColumns ();

	// returns the number of records in the table
	int getSize ();

	// get a single record
	Record getRecord (int index);

	// replace a column name
	int replaceColumnName (string find, string replace);

	// join with another table
	Table join (Table newTable);

	// perform various tasks on columns
	string sum (string name);
	int count (string name);
	string Min (string name);
	string Max (string name);
};