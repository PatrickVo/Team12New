#ifndef RETRIEVER_H_
#define RETRIEVER_H_

#pragma once
#include "QueryCondition.h"
#include "Database.h"

enum PrimaryKey 
{
	Empty,
	userID,
	placeID
};

class Retriever
{
public:
	Retriever();
	Retriever(vector<string> fields, 
		PrimaryKey primaryKeyType, 
		QueryCondition queryCondition);
	Retriever(vector<string> fields, 
		PrimaryKey primaryKeyType, 
		vector<QueryCondition> queryCondition);
	~Retriever(void);

	void AddQueryCondition(QueryCondition queryCondition);
	void AddField(string field);
	void AddFields(vector<string> fields);
	void LinkDatabase(Database& database);
	void SetPrimaryKey(PrimaryKey primaryKey);

	Table GetData(string name = "returnTable");

private:
	vector<string> _tableNames;
	vector<string> _fieldNames;
	vector<QueryCondition> _conditions;
	PrimaryKey _primaryKey;
	Database _database;

};

#endif
