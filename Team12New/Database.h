
#pragma once

#include "Table.h"
#include "Predicate.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class DBDLL_API Database
{
public:

	// Default constructor
	Database ();

	// Default destructor
	~Database ();

	// add table function that returns an error code
	int addTable (Table input, string name);

	// retrieve table by name
	Table getTable (string name);

	// remove table and returns an error code
	int removeTable (string name);

	// returns a list of table names
	vector<string> listTables ();

	// returns all tables
	vector<Table> getTables ();

	// a basic query
	Table query (vector<string> select, string from, string whereTemp);

	// delete tuples from table and returns an error code
	int deleteTuple (vector<string> select, string from, string whereTemp);

private:
	enum ConjunctionType
	{
		AND,
		OR
	};
	map<string, Table> tables;

	bool evaluateQuerySubstring(string substr, Table &table, int recordNum);
	bool checkQueryValidity(string query);
	bool checkPredicateValidity(Predicate predicate);
	Predicate getPredicate(string subQuery);

};