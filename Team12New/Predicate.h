#pragma once
#include <string>
#include "Record.h"
#include "Table.h"

using namespace std;

class Predicate
{
public:
	Predicate();
	Predicate(string attrName, string compare, string val);

	bool evaluate(Table &table, int recordNum);

private:
	enum CompareType
	{
		LESS_THAN,
		LESS_THAN_EQUALS,
		GREATER_THAN,
		GREATER_THAN_EQUALS,
		EQUALS,
		NOT_EQUALS,

		INVALID
	};

	string attributeName;
	CompareType comparison;
	string value;

	bool compareStrings(string str1, string str2, string strType, CompareType comp);

};