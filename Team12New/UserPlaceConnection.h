#ifndef USER_PLACE_CONNECTION_H_
#define USER_PLACE_CONNECTION_H_

#pragma once
#include "Database.h"
#include "Retriever.h"
//#include <fstream>


enum PrimarySelected{
	userPrimary,
	placePrimary
};

class UserPlaceConnection
{
public:
	UserPlaceConnection(void);
	~UserPlaceConnection(void);

	void SetUserID(string userID);
	void SetPlaceID(string placeID);
	void AddComparison(string userField, string placeField);
	void AddSelectField(string field);
	void LinkDatabase(Database& database);
	Table GetData(); 

private:
	PrimarySelected _primarySelected;
	string _userID;
	string _placeID;
	Retriever _userRetriever;
	Retriever _placeRetriever;
	vector<string> _userTableNames;
	vector<string> _userFieldNames;
	vector<string> _placeTableNames;
	vector<string> _placeFieldNames;
	vector<string> _selectTableNames;
	vector<string> _selectFieldNames;
	Database _database;
};

#endif
