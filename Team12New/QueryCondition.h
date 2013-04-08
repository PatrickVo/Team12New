#ifndef QUERY_CONDITION_H_
#define QUERY_CONDITION_H_

#pragma once
#include "Includes.h"

enum QueryOperator {
	None,
	Equals,
	DoesNotEqual,
	GreaterThan,
	LessThan,
	GreaterThanOrEqualTo,
	LessThanOrEqualTo,
	AND,
	OR,
	NOT
};

enum QConditionType {
	Single,
	Multiple
};

class QueryCondition
{
public:
	QueryCondition();
	QueryCondition(string field, QueryOperator queryOperator, string conditionValue);
	QueryCondition(string field, string queryOperatorString, string conditionValue);
	QueryCondition(QueryCondition condition1, QueryCondition condition2, QueryOperator queryOperator);
	QueryCondition(QueryCondition condition1, QueryCondition condition2, string queryOperatorString);
	QueryCondition(vector<QueryCondition> conditions, QueryOperator queryOperator);
	~QueryCondition(void);

	string GetCondition();
	string GetTableName();

private:
	string _tableName;
	string _fieldName;
	string _conditionValue;

	QueryCondition* _condition1;
	QueryCondition* _condition2;

	QueryOperator _queryOperator;
	QConditionType _QConditionType;
};

#endif