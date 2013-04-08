#include "FileReader.h"


//For testing 
void test_vectors(vector<pair<string,string>> _ListofAttributes, vector<string> _records)
{
	for(unsigned int i=0;i<_ListofAttributes.size();i++)
	{
		cout << _ListofAttributes[i].first << " (" << _ListofAttributes[i].second << ")" << endl;
	}

	cout << endl;

	for(unsigned int i=0;i<_records.size();i++)
	{
		cout << _records[i] << endl;
	}
}

void PrintTable(Table table)
{

	ofstream file;
	 file.open ("output.txt");

	vector<pair<string, Attribute>> Attributes = table.getAttributes();	
	for(unsigned int i = 0; i<Attributes.size();i++)
	{
		cout << Attributes[i].first << "\t " << "|";
		file << Attributes[i].first << "\t " << "|";
	}
	cout << endl;
	file << endl;
	for(unsigned int i = 0; i<Attributes.size();i++)
	{
		cout << Attributes[i].second.getType() << "\t " << "|";
		file << Attributes[i].second.getType() << "\t " << "|";
	}
	cout << endl;
	file << endl;

	for(int i = 0; i<table.getSize();i++)
	{
		Record rec = table.getRecord(i);
		for(int k = 0;k<rec.getSize(); k++)
		{
			cout << rec.getEntry(k) << "\t" << "|";
			file << rec.getEntry(k) << "\t" << "|";

		}
		cout << endl;
		file << endl;
	}

    file.close();

}

//Genral Read function
Table ReadFromFile(string FileName, string Attribuestype[])
{	
	ifstream _FileReader;
	string AttributeName; 
	string PushName = "";
	vector<string> _records;
	vector<pair<string,Attribute>> _ListofAttributes;
	_FileReader.open(FileName+".csv");
	
	getline(_FileReader, AttributeName);
	unsigned int i=0;
	unsigned int k=0;

	

	//Hard Code for the Chef Hours file Case
	if(FileName == "chefmozhours4")
	{
		_ListofAttributes.push_back(make_pair(FileName+"."+"placeID",Attribute("Int")));
		_ListofAttributes.push_back(make_pair(FileName+"."+"openHour",Attribute("Float")));
		_ListofAttributes.push_back(make_pair(FileName+"."+"closeHour",Attribute("Float")));
		_ListofAttributes.push_back(make_pair(FileName+"."+"days",Attribute("String")));
	}
	else 
	{
		//Only Reads the first line 		
		while(i<=AttributeName.length())
		{
			//Concat every char into a string untill a comman 
			if(AttributeName[i] == ',' )
			{
			
				//Checks if the string is not read in as a C style string
				if(PushName[PushName.size()-1] == '\0')
					PushName.erase(PushName.size()-1);
				Attribute type(Attribuestype[k]);				
				_ListofAttributes.push_back(make_pair(FileName+"."+PushName,type));

				i++;
				k++;
				PushName ="";
			}
			else
			{			
				PushName = PushName + AttributeName[i];
				i++;
			}
		}
		//Checks if the string is not read in as a C style string
		if(PushName[PushName.size()-1] == '\0')
				PushName.erase(PushName.size()-1);
		Attribute type(Attribuestype[k]);
		_ListofAttributes.push_back(make_pair(FileName+"."+PushName,type));
	}
	
	

	//Addes Attributes into the Table
	Table table(_ListofAttributes);

	PushName = "";	
	string RecordEntry;	
	while(_FileReader.good())
	{
		_records.clear();
		getline(_FileReader, RecordEntry);
		i=0;
		if(RecordEntry != "")
		{
			while(i<=RecordEntry.length())
			{
				//Concat every char into a string untill a comman 			
				if(RecordEntry[i] == ',' || (FileName == "chefmozhours4" && RecordEntry[i] == '-' ))
				{
					//Checks if the string is not read in as a C style string
					if(PushName[PushName.size()-1] == '\0')
						PushName.erase(PushName.size()-1);
					if(PushName == "?")
						_records.push_back("NULL");
					else 
						_records.push_back(PushName);

					i++;
					PushName ="";
				}
				else
				{
					if(RecordEntry[i] == ':')
						PushName = PushName + '.';
					else 
						PushName = PushName + RecordEntry[i];
					i++;
				}
			}
			//Checks if the string is not read in as a C style string
			if(PushName[PushName.size()-1] == '\0')
				PushName.erase(PushName.size()-1);
			if(PushName == "?")
				_records.push_back("NULL");
			else 
				_records.push_back(PushName);		
			//add every record into the table	
			table.insertRecord(_records);

			PushName ="";
		}
	}	
	_FileReader.close();
	//test_vectors(_ListofAttributes, _records);

	return table;
	
}


Table Load_chefmozaccepts()
{
	string FileName = "chefmozaccepts";		
	string AttributeTypes[2] = {"Int","String"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_chefmozcuisine()
{
	string FileName = "chefmozcuisine";		
	string AttributeTypes[2] = {"Int","String"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_chefmozhours4()
{
	string FileName = "chefmozhours4";		
	string AttributeTypes[4] = {"Int","Float","Float","String"};

	 return ReadFromFile(FileName,AttributeTypes);

}
Table Load_chefmozparking()
{
	string FileName = "chefmozparking";		
	string AttributeTypes[2] = {"Int","String"};

	return ReadFromFile(FileName,AttributeTypes);
}
Table Load_rating_final()
{
	string FileName = "rating_final";		
	string AttributeTypes[5] = {"String","Int","Int","Int","Int"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_usercuisine()
{
	string FileName = "usercuisine";		
	string AttributeTypes[2] = {"String","String"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_userpayment()
{
	string FileName = "userpayment";		
	string AttributeTypes[26] = {"String","String"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_userprofile()
{
	string FileName = "userprofile";		
	string AttributeTypes[19] = {"String","Float","Float","String","String",
								 "String","String","String","String","String",
								  "Int","String","String","String","String",
								  "String","Int","String","Float"};

	 return ReadFromFile(FileName,AttributeTypes);
}
Table Load_geoplaces2()
{	
	string FileName = "geoplaces2";		
	string AttributeTypes[26] = {"Int","Float","Float","String","String",
								  "String","String","String","String","String",
								  "Int","String","String","String","String",
								  "Int","String","String","String","String",
								  "String"};

	 return ReadFromFile(FileName,AttributeTypes);
}


void LoadDataBase(Database& database)
{	
	//addes a table to the database for every .csv file
	cout << "Loading....." << endl;
	cout << "[..........] 0%";
	database.addTable(Load_chefmozaccepts(),"chefmozaccepts");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[|.........] 10%";
	database.addTable(Load_chefmozcuisine(),"chefmozcuisines");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[||........] 20%";
	database.addTable(Load_chefmozhours4(),"chefmozhours");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[|||.......] 30%";
	database.addTable(Load_chefmozparking(),"chefmozparking");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[||||......] 40%" << endl;
	database.addTable(Load_geoplaces2(),"geoplaces2");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[||||||....] 60%";
	database.addTable(Load_rating_final(),"finalrating");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[|||||||...] 70%";
	database.addTable(Load_usercuisine(),"usercuisines");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[||||||||..] 80%";
	database.addTable(Load_userpayment(),"userpayment");

	system("cls");
	cout << "Loading....." << endl;
	cout << "[|||||||||.] 90%";
	database.addTable(Load_userprofile(),"userprofile");
	system("cls");

	cout << "Loading....." << endl;
	cout << "[||||||||||] 100%";
	system("cls");
}
