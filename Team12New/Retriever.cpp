#include "Retriever.h"

template< typename T >
bool  Contains(vector<T> vec, T value)
{
	for(int i = 0; i < vec.size(); i++)
		if(vec[i] == value)
			return true;
	return false;
}

Retriever::Retriever()
{
	_tableNames = vector<string>();
	_fieldNames = vector<string>();
	_conditions = vector<QueryCondition>();
	_primaryKey = PrimaryKey::Empty;
	_database = Database();
}

Retriever::Retriever(vector<string> fields, 
					 PrimaryKey primaryKey, 
					 QueryCondition queryCondition)
{
	for(int i = 0; i < fields.size(); i++)
	{
		stringstream stream(fields[i]);
		string tableName = "";
		string fieldName = "";
		stream>>tableName>>fieldName;
		_tableNames.push_back(tableName);
		_fieldNames.push_back(fieldName);
	}

	_primaryKey = primaryKey;
	_conditions.push_back(queryCondition);
	_database = Database();
}
Retriever::Retriever(vector<string> fields, 
					 PrimaryKey primaryKey, 
					 vector<QueryCondition> queryConditions)
{
	for(int i = 0; i < fields.size(); i++)
	{
		stringstream stream(fields[i]);
		string tableName = "";
		string fieldName = "";
		stream>>tableName>>fieldName;
		_tableNames.push_back(tableName);
		_fieldNames.push_back(fieldName);
	}

	_primaryKey = primaryKey;
	_conditions = queryConditions;
	_database = Database();
}

void Retriever::AddQueryCondition(QueryCondition queryCondition)
{
	_conditions.push_back(queryCondition);
}

void Retriever::AddField(string field)
{
	stringstream stream(field);
		string tableName = "";
		string fieldName = "";
		stream>>tableName>>fieldName;
		_tableNames.push_back(tableName);
		_fieldNames.push_back(fieldName);
}

void Retriever::AddFields(vector<string> fields)
{
	for(int i = 0; i < fields.size(); i++)
	{
		stringstream stream(fields[i]);
		string tableName = "";
		string fieldName = "";
		stream>>tableName>>fieldName;
		_tableNames.push_back(tableName);
		_fieldNames.push_back(fieldName);
	}
}

void Retriever::LinkDatabase(Database& database)
{
	_database = database;
}

void Retriever::SetPrimaryKey(PrimaryKey primaryKey)
{
	_primaryKey = primaryKey;
}


string RemoveTableName(string attribute)
{
	int numberOfIterations = attribute.size();
	for(int i = 0; i < numberOfIterations; i++)
	{
		if(attribute[0] == '.')
			i = numberOfIterations;
		attribute.erase(0,1);
	}

	return attribute;
}

Table KeyJoin(Table table1, Table table2, string newTableName, PrimaryKey primaryKeyType, bool outerJoin = false)
{
	string primaryKey;
	switch(primaryKeyType)
	{
	case PrimaryKey::placeID:
		primaryKey = "placeID";
		break;
	case PrimaryKey::userID:
		primaryKey = "userID";
		break;
	}

	Table returnTable = Table();
	int table1PrimaryKeyIndex = -1;
	int table2PrimaryKeyIndex = -1;

	int z = 0;
	string a = newTableName + "." + primaryKey;
	returnTable.addColumn(a, Attribute("String"));
	for(int i = 0; i < table1.getAttributes().size(); i++)
		if(RemoveTableName(table1.getAttributes()[i].first) != primaryKey)
			returnTable.addColumn(table1.getAttributes()[i].first, table1.getAttributes()[i].second);
		else
			table1PrimaryKeyIndex = i;

	for(int i = 0; i < table2.getAttributes().size(); i++)
		if(RemoveTableName(table2.getAttributes()[i].first) != primaryKey)
			returnTable.addColumn(table2.getAttributes()[i].first, table2.getAttributes()[i].second);
		else
			table2PrimaryKeyIndex = i;

	for(int i = 0; i < table1.getSize(); i++)
	{
		Record table1Record = table1.getRecord(i);
		bool matchFound = false;
		for(int j = 0; j < table2.getSize(); j++)
		{
			Record table2Record = table2.getRecord(j);
			string table1PrimaryKey = table1Record.getEntry(table1PrimaryKeyIndex);
			string table2PrimaryKey = table2Record.getEntry(table2PrimaryKeyIndex);
			if( table1PrimaryKey == table2PrimaryKey)
			{
				vector<string> entries;
				entries.push_back(table1PrimaryKey);

				for(int k = 0; k < table1Record.getSize(); k++)
					if(k != table1PrimaryKeyIndex)
						entries.push_back(table1Record.getEntry(k));
				for(int k = 0; k < table2Record.getSize(); k++)
					if(k != table2PrimaryKeyIndex)
						entries.push_back(table2Record.getEntry(k));
				returnTable.insertRecord(Record(entries));
				matchFound = true;
			}
		}
		if(outerJoin)
			if(!matchFound)
			{
				vector<string> entries;
				entries.push_back(table1Record.getEntry(table1PrimaryKeyIndex));
				int j = 0;
				int x = table1Record.getSize();
				for(j = 0; j < x; j++)
					if(j != table1PrimaryKeyIndex)
						entries.push_back(table1Record.getEntry(j));
				int y = returnTable.getAttributes().size();
				for(j; j < y ; j++)
					entries.push_back("NULL");
				returnTable.insertRecord(Record(entries));
			}

	}

	return returnTable;
}


Table Retriever::GetData(string name)
{
	vector< vector<QueryCondition> > queryConditionMatrix;
	queryConditionMatrix.push_back(vector<QueryCondition>());
	queryConditionMatrix[0].push_back(_conditions[0]);

	for(int i = 1; i < _conditions.size(); i++)
	{
		bool tableMatchFound = false;
		for(int j = 0; j < queryConditionMatrix.size(); j++)
		{
			if((queryConditionMatrix[j])[0].GetTableName() == _conditions[i].GetTableName())
			{
				queryConditionMatrix[j].push_back(_conditions[i]);
				tableMatchFound = true; 
				j = queryConditionMatrix.size();
			}
		}

		if(tableMatchFound == false)
		{
			queryConditionMatrix.push_back(vector<QueryCondition>());
			queryConditionMatrix[queryConditionMatrix.size() - 1].push_back(_conditions[i]);
		}
	}


	vector<QueryCondition> finalConditions;
	for(int i = 0; i < queryConditionMatrix.size(); i++)
	{
		QueryCondition condition = queryConditionMatrix[i][0];
		for(int j = 1; j < queryConditionMatrix[i].size(); j++)
			condition = QueryCondition(condition, queryConditionMatrix[i][j], QueryOperator::AND);
		finalConditions.push_back(condition);
	}

	Database databaseLocal = Database();
	vector<string> all;
	all.push_back("*");
	string a = finalConditions[0].GetCondition();
	for(int i = 0; i < finalConditions.size(); i++)
		databaseLocal.addTable(_database.query(all, finalConditions[i].GetTableName(), finalConditions[i].GetCondition()),finalConditions[i].GetTableName());
	
	Table masterTable = Table();

	if(databaseLocal.getTables().size() > 1)
	{
		masterTable = KeyJoin(
			databaseLocal.getTables()[0],
			databaseLocal.getTables()[1],
			name,
			_primaryKey);
		for(int i = 2; i < databaseLocal.getTables().size(); i++)
			masterTable = KeyJoin(
							masterTable, 
							databaseLocal.getTables()[i], 
							name,
							_primaryKey);
	}
	else
		masterTable = databaseLocal.getTables()[0];

	vector<string> tablesAlreadyQueued = databaseLocal.listTables();		
	vector<string> reducedTableList;
	reducedTableList.push_back(_fieldNames[0]);
	for(int i = 0; i < _tableNames.size(); i++)
		if(!Contains(reducedTableList, _tableNames[i]))
			reducedTableList.push_back(_tableNames[i]);
	for(int i = 0; i < reducedTableList.size(); i++)
	{
		if(!Contains(tablesAlreadyQueued, reducedTableList[i]))
			masterTable = KeyJoin(
						masterTable,
						_database.getTable(reducedTableList[i]),
						name,
						_primaryKey,
						true);
	}


	Database databaseFinal = Database();
	databaseFinal.addTable(masterTable, "table");

	vector<string> fieldsToQuery;
	for(int i = 0; i < _tableNames.size(); i++)
		if(_fieldNames[i] == "placeID")
			fieldsToQuery.push_back(name + "." + _fieldNames[i]);
		else if(_fieldNames[i] == "userID")
			fieldsToQuery.push_back(name + "." + _fieldNames[i]);
		else
		fieldsToQuery.push_back(_tableNames[i] + "." + _fieldNames[i]);

	return databaseFinal.query(fieldsToQuery,"table",fieldsToQuery[0] + " != -100000"); //needs to be fixed
}



Retriever::~Retriever(void)
{
}