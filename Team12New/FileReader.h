#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Database.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;

void test_vectors(vector<pair<string,string>> _ListofAttributes, vector<string> _records);

void PrintTable(Table table);

Table ReadFromFile(string FileName, string Attribuestype[]);

//Sent the file name and array of types to the General Read function
Table Load_chefmozaccepts();
Table Load_chefmozcuisine();
Table Load_chefmozhours4();
Table Load_chefmozparking();
Table Load_rating_final();
Table Load_usercuisine();
Table Load_userpayment();
Table Load_userprofile();
Table Load_geoplaces2();

void LoadDataBase(Database& database);

#endif