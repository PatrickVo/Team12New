#include "UserPlaceConnection.h"


UserPlaceConnection::UserPlaceConnection(void)
{
}

void UserPlaceConnection::SetUserID(string userID)
{
	_userID = userID;
	_primarySelected = PrimarySelected::userPrimary;
}

void UserPlaceConnection::SetPlaceID(string placeID)
{
	_placeID = placeID;
	_primarySelected = PrimarySelected::placePrimary;
}

void UserPlaceConnection::AddComparison(string userField, string placeField)
{
	stringstream userStream(userField);
	string userTableName = "";
	string userFieldName = "";
	userStream>>userTableName>>userFieldName;
	_userTableNames.push_back(userTableName);
	_userFieldNames.push_back(userFieldName);

	stringstream placeStream(placeField);
	string placeTableName = "";
	string placeFieldName = "";
	placeStream>>placeTableName>>placeFieldName;
	_placeTableNames.push_back(placeTableName);
	_placeFieldNames.push_back(placeFieldName);

}

void UserPlaceConnection::AddSelectField(string field)
{
	stringstream stream(field);
	string tableName = "";
	string fieldName = "";
	stream>>tableName>>fieldName;
	_selectTableNames.push_back(tableName);
	_selectFieldNames.push_back(fieldName);
}

string RemoveTableName2(string attribute)
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

Table MultipleConditionJoin(Table table1, Table table2, vector<string> table1Fields, vector<string> table2Fields)
{
	Table returnTable = Table();
	vector<int> table1PrimaryKeyIndexes;
	vector<int> table2PrimaryKeyIndexes;

	for(int i = 0; i < table1Fields.size(); i++)
	{
		for(int j = 0; j < table1.getColumns().size(); j++)
			if(table1Fields[i] == table1.getColumns()[j].first)
			{
				table1PrimaryKeyIndexes.push_back(j);
				j = table1.getColumns().size();
			}
	}

	for(int i = 0; i < table2Fields.size(); i++)
	{
		for(int j = 0; j < table2.getColumns().size(); j++)
			if(table2Fields[i] == table2.getColumns()[j].first)
			{
				table2PrimaryKeyIndexes.push_back(j);
				j = table2.getColumns().size();
			}
	}

	for(int i = 0; i < table1.getAttributes().size(); i++)
		if(RemoveTableName2(table1.getAttributes()[i].first) == "userID" |
			RemoveTableName2(table1.getAttributes()[i].first) == "placeID" )
				returnTable.addColumn(table1.getAttributes()[i].first, table1.getAttributes()[i].second);
		else
				returnTable.addColumn("main." + RemoveTableName2(table1.getAttributes()[i].first), table1.getAttributes()[i].second);

	for(int i = 0; i < table2.getAttributes().size(); i++)
		if(RemoveTableName2(table2.getAttributes()[i].first) == "userID" |
			RemoveTableName2(table2.getAttributes()[i].first) == "placeID" )
				returnTable.addColumn(table2.getAttributes()[i].first, table2.getAttributes()[i].second);
		else
				returnTable.addColumn("main." + RemoveTableName2(table2.getAttributes()[i].first), table2.getAttributes()[i].second);

	for(int i = 0; i < table1.getSize(); i++)
	{
		for(int j = 0; j < table2.getSize(); j++)
		{
			bool allEqual = true;
			for(int k = 0; k < table1Fields.size(); k++)
			{
				if(
					table1.getRecord(i).getEntry(table1PrimaryKeyIndexes[k]) !=
					table2.getRecord(j).getEntry(table2PrimaryKeyIndexes[k]))
				{
					k = table1Fields.size();
					allEqual = false;
				}
			}
			if(allEqual)
			{
				vector<string> entries;
				for(int k = 0; k < table1.getRecord(i).getSize(); k++)
					entries.push_back(table1.getRecord(i).getEntry(k));
				for(int k = 0; k < table2.getRecord(j).getSize(); k++)
					entries.push_back(table2.getRecord(j).getEntry(k));

				returnTable.insertRecord(Record(entries));
			}
		}
	}
	return returnTable;
}

void UserPlaceConnection::LinkDatabase(Database& database)
{
	_database = database;
}

Table UserPlaceConnection::GetData()
{
	_userRetriever = Retriever();
	_placeRetriever = Retriever();

	_userRetriever.AddField(_userTableNames[0] + " " + "userID");
	for(int i = 0; i < _userTableNames.size(); i++)
		_userRetriever.AddField(_userTableNames[i] + " " + _userFieldNames[i]);
	
	_placeRetriever.AddField(_placeTableNames[0] + " " + "placeID");
	for(int i = 0; i < _placeTableNames.size(); i++)
		_placeRetriever.AddField(_placeTableNames[i] + " " + _placeFieldNames[i]);

	string idString;
	switch(_primarySelected)
	{
	case PrimarySelected::placePrimary:
		_userRetriever.AddQueryCondition(
			QueryCondition(
				_userTableNames[0] + " " + "userID",
				QueryOperator::DoesNotEqual,
				"-10000"));
		_placeRetriever.AddQueryCondition(
			QueryCondition(
				_placeTableNames[0] + " " + "placeID",
				QueryOperator::Equals,
				_placeID));
		idString = "userID";
		break;
	case PrimarySelected::userPrimary:
		_userRetriever.AddQueryCondition(
			QueryCondition(
				_userTableNames[0] + " " + "userID",
				QueryOperator::Equals,
				_userID));
		_placeRetriever.AddQueryCondition(
			QueryCondition(
				_placeTableNames[0] + " " + "placeID",
				QueryOperator::DoesNotEqual,
				"-10000"));
		idString = "placeID";
		break;
	}

	_userRetriever.LinkDatabase(_database);
	_placeRetriever.LinkDatabase(_database);

	_userRetriever.SetPrimaryKey(PrimaryKey::userID);
	_placeRetriever.SetPrimaryKey(PrimaryKey::placeID);
	
	vector<string> userRequiredFields;
	vector<string> placeRequiredFields;
	for(int i = 0; i < _userTableNames.size(); i++)
		userRequiredFields.push_back(_userTableNames[i]+"."+_userFieldNames[i]);
	for(int i = 0; i < _placeTableNames.size(); i++)
		placeRequiredFields.push_back(_placeTableNames[i]+"."+_placeFieldNames[i]);
	
	Table t1 = Table();
	Table t2 = Table();

	switch(_primarySelected)
	{
	case PrimarySelected::placePrimary:
		t2 = _placeRetriever.GetData("placeID");

		for(int i = 0; i < userRequiredFields.size(); i++)
			_userRetriever.AddQueryCondition(
				QueryCondition(
					_userTableNames[i] + " " + _userFieldNames[i],
					QueryOperator::Equals,
					t2.getRecord(0).getEntry(i+1)));

		t1 = _userRetriever.GetData("userID");
		break;
	case PrimarySelected::userPrimary:
		t1 = _userRetriever.GetData("userID");

		for(int i = 0; i < placeRequiredFields.size(); i++)
			_placeRetriever.AddQueryCondition(
				QueryCondition(
					_placeTableNames[i] + " " + _placeFieldNames[i],
					QueryOperator::Equals,
					t1.getRecord(0).getEntry(i+1)));

		t2 = _placeRetriever.GetData("placeID");
		break;
	}	

	Table joinTable = MultipleConditionJoin(
					t1,
					t2,
					userRequiredFields,
					placeRequiredFields);
	
	_database.addTable(joinTable, idString);
	
	Retriever retrieverFinal = Retriever();

	retrieverFinal.AddQueryCondition(QueryCondition(idString + " " + idString,QueryOperator::DoesNotEqual, "-10000"));
	for(int i = 0; i < _selectFieldNames.size(); i++)
		retrieverFinal.AddField(_selectTableNames[i] + " " + _selectFieldNames[i]);

	retrieverFinal.LinkDatabase(_database);
	switch(_primarySelected)
	{
	case PrimarySelected::placePrimary:
		retrieverFinal.SetPrimaryKey(PrimaryKey::userID);
		break;
	case PrimarySelected::userPrimary:
		retrieverFinal.SetPrimaryKey(PrimaryKey::placeID);
		break;
	}

	return retrieverFinal.GetData();
}

UserPlaceConnection::~UserPlaceConnection(void)
{
}
