#include "QueryCondition.h"

QueryCondition::QueryCondition()
{
	_queryOperator = QueryOperator::None;
}

QueryCondition::QueryCondition(string field, QueryOperator queryOperator, string conditionValue)
{
	stringstream stream(field);
	stream>>_tableName>>_fieldName;
	_queryOperator = queryOperator;
	_conditionValue = conditionValue;
	_QConditionType = QConditionType::Single;
}

QueryCondition::QueryCondition(string field, string queryOperatorString, string conditionValue)
{
	stringstream stream(field);
	stream>>_tableName>>_fieldName;
	_conditionValue = conditionValue;
	_QConditionType = QConditionType::Single;

	if(queryOperatorString == "=")
		_queryOperator = QueryOperator::Equals;
	else if(queryOperatorString == "!=")
		_queryOperator = QueryOperator::DoesNotEqual;
	else if(queryOperatorString == ">")
		_queryOperator = QueryOperator::GreaterThan;
	else if(queryOperatorString == "<")
		_queryOperator = QueryOperator::LessThan;
	else if(queryOperatorString == ">=")
		_queryOperator = QueryOperator::GreaterThanOrEqualTo;
	else if(queryOperatorString == "<=")
		_queryOperator = QueryOperator::LessThanOrEqualTo;
	else
		_queryOperator = QueryOperator::None;
}

QueryCondition::QueryCondition(QueryCondition condition1, QueryCondition condition2, QueryOperator queryOperator)
{
	_condition1 = new QueryCondition(condition1);
	_condition2 = new QueryCondition(condition2);
	_queryOperator = queryOperator;
	_QConditionType = QConditionType::Multiple;
	_tableName = condition1.GetTableName();
}

QueryCondition::QueryCondition(QueryCondition condition1, QueryCondition condition2, string queryOperatorString)
{
	_condition1 = new QueryCondition(condition1);
	_condition2 = new QueryCondition(condition2);
	_QConditionType = QConditionType::Multiple;
	_tableName = condition1.GetTableName();

	if(queryOperatorString == "AND")
		_queryOperator = QueryOperator::AND;
	else if(queryOperatorString == "OR")
		_queryOperator = QueryOperator::OR;
	else if(queryOperatorString == "NOT")
		_queryOperator = QueryOperator::NOT;
	else
		_queryOperator = QueryOperator::None;
}

QueryCondition::QueryCondition(vector<QueryCondition> conditions, QueryOperator queryOperator)
{
	QueryCondition* condition = new QueryCondition(conditions[0]);
	for(int i = 1; i < conditions.size(); i++)
		condition = new QueryCondition(*condition, conditions[i], queryOperator);

	_condition1 = condition->_condition1;
	_condition2 = condition->_condition2;
	_queryOperator = queryOperator;
	_QConditionType = QConditionType::Multiple;
	_tableName = conditions[0].GetTableName();

}


string QueryCondition::GetCondition()
{
	string operatorString = "";
	switch(_queryOperator)
	{
	case QueryOperator::None:
		return "";
		break;
	case QueryOperator::Equals:
		operatorString = " = ";
		break;
	case QueryOperator::DoesNotEqual:
		operatorString = " != ";
		break;
	case QueryOperator::GreaterThan:
		operatorString = " > ";
		break;
	case QueryOperator::LessThan:
		operatorString = " < ";
		break;
	case QueryOperator::GreaterThanOrEqualTo:
		operatorString = " >= ";
		break;
	case QueryOperator::LessThanOrEqualTo:
		operatorString = " <= ";
		break;
	case QueryOperator::AND:
		operatorString = " AND ";
		break;
	case QueryOperator::OR:
		operatorString = " OR ";
		break;
	case QueryOperator::NOT:
		operatorString = " NOT "; //will not yet work
		break;
	}
	string result = "";
	switch(_QConditionType)
	{
	case QConditionType::Single:
		return _tableName + "." + _fieldName + operatorString + _conditionValue;
		break;
	case QConditionType::Multiple:
		return "( " +_condition1->GetCondition() + " " + operatorString + " " +_condition2->GetCondition() + " )";
		break;
	}

	return "";
}

string QueryCondition::GetTableName()
{
	return _tableName;
}

QueryCondition::~QueryCondition(void)
{
}
