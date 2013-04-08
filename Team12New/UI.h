#include "Includes.h"
#include "QueryCondition.h"
#include "Retriever.h"
#include "UserPlaceConnection.h"

//Retriever retriever;
//UserPlaceConnection USERPLACECONNECTION;

string Welcome = "\n\nEnter what you are searching for:" 
	 "\n1 - Information about a customer"
	 "\n2 - Information about a restaurant"
	 "\n3 - Restaurants that match a customer"
	 "\n4 - Customers that match a restaurant"
	 "\n5 - Search for customers matching a criteria"
	 "\n6 - Search for restaurants matching a criteria"
	 //"\n7 - Ratings information"
	 "\nq - Exit database\n";

string InfoInstructions = "\nPlease input which pieces of information you desire."
		"\nEnter each number, pressing enter after each number"
		"\nand entering a semicolon (;) when finished.\n";

string MatchInstructions = "\nPlease input the pieces of information you wish to match."
		"\nEnter each number, pressing enter after each number"
		"\nand entering a semicolon (;) when finished.\n";

string CriteriaInstructions = "\nPlease input the pieces of information you wish to search."
		"\nEnter each number, pressing enter after each number"
		"\nand entering a semicolon (;) when finished.\n";

// Function Declarations
void InformationAboutCustomer(Retriever& retriever);
void InformationAboutRestaurant(Retriever& retriever);
void MatchRestaurantToCustomer(Retriever& retriever);
void MatchCustomerToRestaurant(Retriever& retriever);
void SearchCustomerCriteria(Retriever& retriever);
void SearchRestaurantCriteria(Retriever& retriever);
void RestaurantSearch(vector<int> optionsVec, Retriever& retriever);
void CustomerSearch(vector<int> optionsVec,  Retriever& retriever);
void RatingsInformation(Retriever& retriever);

int StringToInt(string str);
string IntToString(int num);
float StringToFloat(string str);
string FloatToString(float num);

int SyntaxCheck(string str);


void InvalidMenuOption();

void DetermineInitialDecision(int userInput, Retriever& retriever) {

	switch(userInput) {
		case 1:
			InformationAboutCustomer(retriever);
			break;
		case 2:
			InformationAboutRestaurant();
			break;
		case 3:
			MatchRestaurantToCustomer();
			break;
		case 4:
			MatchCustomerToRestaurant();
			break;
		case 5:
			SearchCustomerCriteria();
			break;
		case 6:
			SearchRestaurantCriteria(retriever);
			break;
		case 7:
			RatingsInformation();
			break;
		default:
			InvalidMenuOption();
			break;
	}

}

// Function Definitions
void InformationAboutCustomer(Retriever& retriever) {
	cout << "\nPlease enter the UserID: ";
	string userID = "";
	cin >> userID;
	retriever.AddQueryCondition(
		QueryCondition(
			"userprofile userID",
			QueryOperator::Equals,
			userID));
	retriever.SetPrimaryKey(PrimaryKey::userID);
	retriever.AddField("userprofile userID");

	cout << InfoInstructions <<
		"\n1 - Location"
		"\n2 - Smokes"
		"\n3 - Alcohol Intake"
		"\n4 - Dress Preference"
		"\n5 - Ambience"
		"\n6 - Method of Transportation"
		"\n7 - Marital Status"
		"\n8 - Children"
		"\n9 - Birth Year"
		"\n10 - Personal Interest"
		"\n11 - Personality"
		"\n12 - Religion"
		"\n13 - Employement Status"
		"\n14 - Favoite Color"
		"\n15 - Budget"
		"\n16 - Weight"
		"\n17 - Height"
		"\n18 - Cuisine Preference"
		"\n19 - Preferred Payment Method";

	cout<<endl;
	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;

		else if(userInputVerified > 20 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";
		
		else
			optionsVec.push_back(userInputVerified);
	}	

	cout << "\nOPTIONS SELECTED...\n";
	
	for(unsigned int i=0; i < optionsVec.size(); i++)	
	{
		switch(optionsVec[i])
		{
			case 1:
				retriever.AddField("userprofile latitude");
				retriever.AddField("userprofile longitude"); 
				break;
			case 2:
				retriever.AddField("userprofile smoker");
				break;
			case 3:
				retriever.AddField("userprofile drink_level");
				break;
			case 4:
				retriever.AddField("userprofile drink_level");
				break;
			case 5: 
				retriever.AddField("userprofile dress_preference");
				break;
			case 6:
				retriever.AddField("userprofile ambience");
				break;
			case 7:
				retriever.AddField("userprofile transport");
				break;
			case 8:
				retriever.AddField("userprofile marital_status");
				break;
			case 9:
				retriever.AddField("userprofile hijos");
				break;
			case 10:
				retriever.AddField("userprofile birth_year");
				break;
			case 11:
				retriever.AddField("userprofile interest");
				break;
			case 12:
				retriever.AddField("userprofile ambience");
				break;
			case 13:
				retriever.AddField("userprofile personality");
				break;
			case 14:
				retriever.AddField("userprofile religon");
				break;
			case 15:
				retriever.AddField("userprofile activity");
				break;
			case 16:
				retriever.AddField("userprofile color");
				break;
			case 17:
				retriever.AddField("userprofile weight");
				break;
			case 18:
				retriever.AddField("userprofile budget");
				break;
			case 19:
				retriever.AddField("userprofile height");
				break;
		}
	}

}

void InformationAboutRestaurant(Retriever& retriever) {
	cout << "\nPlease enter the PlaceID: ";
	string placeID = "";
	cin >> placeID;

	retriever.AddQueryCondition(
		QueryCondition(
			"geoplaces2 placeID",
			QueryOperator::Equals,
			placeID));
	retriever.SetPrimaryKey(PrimaryKey::placeID);
	retriever.AddField("geoplaces2 placeID");

	cout << InfoInstructions <<
		"\n1 - Location"
		"\n2 - Restuarant Name"
		"\n3 - Address"
		"\n4 - Alcohol Service"
		"\n5 - Smoking Area"
		"\n6 - Dress Code"
		"\n7 - Accessibility"
		"\n8 - Price"
		"\n9 - Website"
		"\n10 - Ambience"
		"\n11 - Franchise Status"
		"\n12 - Area"
		"\n13 - Other Services"
		"\n14 - Hours of Operation"
		"\n15 - Cuisine"
		"\n16 - Method of Payment Accepted"
		"\n17 - Parking Options\n";

	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;

		else if(userInputVerified > 17 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";
		
		else
			optionsVec.push_back(userInputVerified);
	}

	cout << "\nOPTIONS SELECTED...\n";
	
	for(unsigned int i=0; i < optionsVec.size(); i++)
	{
		switch(optionsVec[i])
		{
			case 1:
				retriever.AddField("geoplaces2 latitude");
				retriever.AddField("geoplaces2 longitude"); 
				break;
			case 2:
				retriever.AddField("geoplaces2 name");
				break;
			case 3:
				retriever.AddField("geoplaces2 address");
				break;
			case 4:
				retriever.AddField("geoplaces2 alcohol");
				break;
			case 5: 
				retriever.AddField("geoplaces2 smoking_area");
				break;
			case 6:
				retriever.AddField("geoplaces2 dress_code");
				break;
			case 7:
				retriever.AddField("geoplaces2 accessibility");
				break;
			case 8:
				retriever.AddField("userprofile price");
				break;
			case 9:
				retriever.AddField("geoplaces2 url");
				break;
			case 10:
				retriever.AddField("geoplaces2 Rambience");
				break;
			case 11:
				retriever.AddField("geoplaces2 franchise");
				break;
			case 12:
				retriever.AddField("geoplaces2 area");
				break;
			case 13:
				retriever.AddField("geoplaces2 other_services");
				break;
			case 14:
				retriever.AddField("chefmozhours openHour");
				retriever.AddField("chefmozhours closeHour");
				break;
			case 15:
				retriever.AddField("chefmozcuisine Rcuisine");
				break;
			case 16:
				retriever.AddField("chefmozaccepts Rpayment");
				break;
			case 17:
				retriever.AddField("chefmozparking parking_lot");
				break;
			
		}
	}
}

void MatchRestaurantToCustomer(Retriever& retriever) {
	cout << "\nPlease enter the UserID: ";
	string userID;
	cin >> userID;

	cout << MatchInstructions <<
		"\n1 - GPS Location"
		"\n2 - Smokes"
		"\n3 - Alcohol Intake"
		"\n4 - Dress Preference"
		"\n5 - Ambience"
		"\n6 - Budget"
		"\n7 - Cuisine Preference"
		"\n8 - Preferred Payment Method\n";

	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;

		else if(userInputVerified > 8 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";
		
		else
			optionsVec.push_back(userInputVerified);
	}

	cout << "\nOPTIONS SELECTED...\n";

	for(unsigned int i=0; i < optionsVec.size(); i++)
		cout << optionsVec[i] << endl;
}

void MatchCustomerToRestaurant(Retriever& retriever) {
	cout << "\nPlease enter the PlaceID: ";
	string placeID;
	cin >> placeID;

	cout << MatchInstructions <<
		"\n1 - Location"
		"\n2 - Alcohol Service"
		"\n3 - Smoking Area"
		"\n4 - Dress Code"
		"\n5 - Price"
		"\n6 - Ambience"
		"\n7 - Cuisine"
		"\n8 - Method of Payment Accepted";

	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;

		else if(userInputVerified > 8 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";
		
		else
			optionsVec.push_back(userInputVerified);
	}

	cout << "\nOPTIONS SELECTED...\n";

	for(unsigned int i=0; i < optionsVec.size(); i++)
		cout << optionsVec[i] << endl;
}

void SearchCustomerCriteria(Retriever& retriever) {
	cout << CriteriaInstructions <<
		"\n1 - Location"
		"\n2 - Smokes"
		"\n3 - Alcohol Intake"
		"\n4 - Dress Preference"
		"\n5 - Ambience"
		"\n6 - Method of Transportation"
		"\n7 - Marital Status"
		"\n8 - Children"
		"\n9 - Birth Year"
		"\n10 - Personal Interest"
		"\n11 - Personality"
		"\n12 - Religion"
		"\n13 - Employement Status"
		"\n14 - Favorite Color"
		"\n15 - Budget"
		"\n16 - Weight"
		"\n17 - Height"
		"\n18 - Cuisine Preference"
		"\n19 - Preferred Payment Method\n";

	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;
		
		else if(userInputVerified > 19 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";

		else
			optionsVec.push_back(userInputVerified);
	}

	cout << "\nOPTIONS SELECTED...\n";

	for(unsigned int i=0; i < optionsVec.size(); i++)
		cout << optionsVec[i] << endl;

	//char c;
	//cin >> c;
	
	if(optionsVec.size() != 0)
		CustomerSearch(optionsVec, retriever);

}

void SearchRestaurantCriteria(Retriever& retriever) {
	retriever.SetPrimaryKey(PrimaryKey::placeID);
	retriever.AddField("geoplaces2 placeID");
	retriever.AddField("geoplaces2 name");
	retriever.AddField("geoplaces2 address");
	retriever.AddField("geoplaces2 city");
	retriever.AddField("geoplaces2 state");

	cout << InfoInstructions <<
		"\n1 - Location"
		"\n2 - Restuarant Name"
		"\n3 - Address"
		"\n4 - Alcohol Service"
		"\n5 - Smoking Area"
		"\n6 - Dress Code"
		"\n7 - Accessibility"
		"\n8 - Price"
		"\n9 - Website"
		"\n10 - Ambience"
		"\n11 - Franchise Status"
		"\n12 - Area"
		"\n13 - Other Services"
		"\n14 - Hours of Operation"
		"\n15 - Cuisine"
		"\n16 - Method of Payment Accepted"
		"\n17 - Parking Options\n";

	vector<int> optionsVec;
	string userInput = "";
	while(userInput != ";") {
		cout << ">> ";
		cin >> userInput;

		int userInputVerified = StringToInt(userInput);

		if(userInput == ";")
			break;

		else if(userInputVerified > 17 || userInputVerified < 1)
			cout << "\nInvalid option. Try again...\n\n";
		
		else
			optionsVec.push_back(userInputVerified);
	}

	cout << "\nOPTIONS SELECTED...\n";

	RestaurantSearch(optionsVec, retriever);
}

void RatingsInformation() {
	cout << "Which ratings information would you like?\n"
		"\n1 - Business"
		"\n2 - Customer\n\n";

	string userInput = "";
	cout << ">> ";
	cin >> userInput;
	int userInputVerified = StringToInt(userInput);

	if(userInputVerified == -1)
		cout << "\nInvalid option. Try again...\n\n";
	else {
		switch(userInputVerified) {
			case 1: {	// business
				cout << "\nPlease enter the PlaceID: ";
				string placeID = "";
				cin >> placeID;

				cout << "BUSINESS RATING INFO\n";

				break;
			}
			case 2: {	// customer
				cout << "\nPlease enter the UserID: ";
				string userID = "";
				cin >> userID;

				cout << "CUSTOMER RATING INFO\n";

				break;
			}
		}
	}
}

void InvalidMenuOption() {
	cout << "Invalid Menu Option..." << endl;
}

// Utility Function
int StringToInt(string str) {
	for(unsigned int i = 0; i < str.size(); i++) {
		if(!isdigit(str[i])) {
			return -1;
		}
	}

	stringstream stream(str);
	int num = 0;
	stream >> num;
	return num;
}

string IntToString(int num) {
	string str = "";
	stringstream stream;

	stream << num;
	str = stream.str();
	return str;
}

float StringToFloat(string str) {
	stringstream stream(str);
	float num = 0.0;
	stream >> num;
	return num;
}

string FloatToString(float num) {
	string str = "";
	stringstream stream;

	stream << num;
	str = stream.str();
	return str;
}

void CustomerSearch(vector<int> optionsVec,  Retriever& retriever) {
	
	retriever.AddQueryCondition(
		QueryCondition(
			"userprofile userID",
			QueryOperator::DoesNotEqual,
			"U9999"));

	for(unsigned int i=0; i<optionsVec.size(); i++) {
	
		int queryOption = optionsVec[i];

		switch(queryOption) {
			case 1: {	// userprofile latitude, longitude

				retriever.AddField("userprofile latitude");
				retriever.AddField("userprofile longitude");

				cout << "\nWhat location would you like to search for?\n";

				cout << "Max Latitude: ";
				string maxLat = "";
				cin >> maxLat;
				
				cout << "Min Latitude: ";
				string minLat = "";
				cin >> minLat;

				cout << "Max Longitude: ";
				string maxLon = "";
				cin >> maxLon;

				cout << "Min Longitude: ";
				string minLon = "";
				cin >> minLon;

				vector<QueryCondition> queryConditions;

				queryConditions.push_back(
					QueryCondition(
						"userprofile smoker",
						QueryOperator::LessThan,
						maxLat));

				queryConditions.push_back(
					QueryCondition(
						"userprofile smoker",
						QueryOperator::GreaterThan,
						minLat));

				queryConditions.push_back(
					QueryCondition(
						"userprofile smoker",
						QueryOperator::LessThan,
						maxLon));

				queryConditions.push_back(
					QueryCondition(
						"userprofile smoker",
						QueryOperator::GreaterThan,
						minLon));

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 2:	{	// userprofile smoker

				retriever.AddField("userprofile smoker");				

				cout << "\nWhat smoking preference would you like to search for?\n"
					"1 - Smoker\n"
					"2 - Non-smoker\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 2 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile smoker",
								QueryOperator::Equals,
								"TRUE"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile smoker",
								QueryOperator::Equals,
								"FALSE"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 3: {	// userprofile drink_level

				retriever.AddField("userprofile drink_level");	

				cout << "\nWhat alcohol intake would you like to search for?\n"
					"1 - Abstemious\n"
					"2 - Casual Drinker\n"
					"3 - Social Drinker\n\n";
					
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile drink_level",
								QueryOperator::Equals,
								"abstemious"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile drink_level",
								QueryOperator::Equals,
								"'casual drinker'"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile drink_level",
								QueryOperator::Equals,
								"'social drinker'"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 4: {	// userprofile dress_preference

				retriever.AddField("userprofile dress_preference");	

				cout << "\nWhat dress preference would you like to search for?\n"
					"1 - Elegant\n"
					"2 - Formal\n"
					"3 - Informal\n"
					"4 - No Preference\n\n";

				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 4 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile dress_preference",
								QueryOperator::Equals,
								"elegant"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile dress_preference",
								QueryOperator::Equals,
								"formal"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile dress_preference",
								QueryOperator::Equals,
								"informal"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile dress_preference",
								QueryOperator::Equals,
								"'no preference'"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 5: {	// userprofile ambience

				retriever.AddField("userprofile ambience");	

				cout << "\nWhat ambience would you like to search for?\n"
					"1 - Family\n"
					"2 - Friends\n"
					"3 - Solitary\n\n";

				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile ambience",
								QueryOperator::Equals,
								"family"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile ambience",
								QueryOperator::Equals,
								"friends"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile ambience",
								QueryOperator::Equals,
								"solitary"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 6: {	// userprofile transport

				retriever.AddField("userprofile transport");	

				cout << "\nWhat method of transportation would you like to search for?\n"
					"1 - On Foot\n"
					"2 - Car Owner\n"
					"3 - Public\n\n";				
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile transport",
								QueryOperator::Equals,
								"'on foot'"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile transport",
								QueryOperator::Equals,
								"'car owner'"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile transport",
								QueryOperator::Equals,
								"public"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 7: {	// userprofile marital_status


				retriever.AddField("userprofile marital_status");	

				cout << "\nWhat marital status would you like to search for?\n"
					"1 - Single\n"
					"2 - Married\n"
					"3 - Widow\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile marital_status",
								QueryOperator::Equals,
								"single"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile marital_status",
								QueryOperator::Equals,
								"married"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile marital_status",
								QueryOperator::Equals,
								"widow"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 8: {	// userprofile hijos

				retriever.AddField("userprofile hijos");	

				cout << "\nWhat child status would you like to search for?\n"
					"1 - Independent\n"
					"2 - Dependent\n"
					"3 - Kids\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile hijos",
								QueryOperator::Equals,
								"independent"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile hijos",
								QueryOperator::Equals,
								"dependent"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile hijos",
								QueryOperator::Equals,
								"kids"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 9: {	// userprofile birth_year

				retriever.AddField("userprofile birth_year");	

				cout << "\nWhat birth year (formatted: yyyy) would you like to search for?\n";
				
				vector<string> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;

					else if(userInputVerified == -1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInput);
				}

				vector<QueryCondition> queryConditions;
				
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					queryConditions.push_back(
						QueryCondition(
							"userprofile birth_year",
							QueryOperator::Equals,
							optionsVec[i]));
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 10: {	// userprofile interest

				retriever.AddField("userprofile interest");	

				cout << "\nWhat personal interest would you like to search for?\n"
					"1 - Technology\n"
					"2 - Retro\n"
					"3 - Eco-friendly\n"
					"4 - Variety\n"
					"5 - None\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 5 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile interest",
								QueryOperator::Equals,
								"technology"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile interest",
								QueryOperator::Equals,
								"retro"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile interest",
								QueryOperator::Equals,
								"eco-friendly"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile interest",
								QueryOperator::Equals,
								"variety"));
						break;
					case 5:
						queryConditions.push_back(
							QueryCondition(
								"userprofile interest",
								QueryOperator::Equals,
								"none"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 11: {	// userprofile personality

				retriever.AddField("userprofile personality");	

				cout << "\nWhat personality would you like to search for?\n"
					"1 - Thrifty-protector\n"
					"2 - Hunter-ostentatious\n"
					"3 - Hard-worker\n"
					"4 - Conformist\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 4 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile personality",
								QueryOperator::Equals,
								"thrifty-protector"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile personality",
								QueryOperator::Equals,
								"hunter-ostentatious"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile personality",
								QueryOperator::Equals,
								"hard-worker"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile personality",
								QueryOperator::Equals,
								"conformist"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 12: {	// userprofile religion

				retriever.AddField("userprofile religion");	

				cout << "\nWhat religion would you like to search for?\n"
					"1 - Catholic\n"
					"2 - Christian\n"
					"3 - Mormon\n"
					"4 - Jewish\n"
					"5 - None\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 5 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile religion",
								QueryOperator::Equals,
								"Catholic"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile religion",
								QueryOperator::Equals,
								"Christian"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile religion",
								QueryOperator::Equals,
								"Mormon"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile religion",
								QueryOperator::Equals,
								"Jewish"));
						break;
					case 5:
						queryConditions.push_back(
							QueryCondition(
								"userprofile religion",
								QueryOperator::Equals,
								"none"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 13: {	// userprofile activity

				retriever.AddField("userprofile activity");	

				cout << "\nWhat employment status would you like to search for?\n"
					"1 - Professional\n"
					"2 - Working-class\n"
					"3 - Student\n"
					"4 - Unemployed\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 4 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile activity",
								QueryOperator::Equals,
								"professional"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile activity",
								QueryOperator::Equals,
								"working-class"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile activity",
								QueryOperator::Equals,
								"student"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile activity",
								QueryOperator::Equals,
								"unemployed"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 14: {	// userprofile color

				retriever.AddField("userprofile color");	

				cout << "\nWhat favorite color would you like to search for?\n";
				
				vector<string> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					if(userInput == ";")
						break;

					else
						optionsVec.push_back(userInput);
				}

				vector<QueryCondition> queryConditions;
				
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					queryConditions.push_back(
						QueryCondition(
							"userprofile color",
							QueryOperator::Equals,
							optionsVec[i]));
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 15: {	// userprofile budget

				retriever.AddField("userprofile budget");	

				cout << "\nWhat budget status would you like to search for?\n"
					"1 - High\n"
					"2 - Medium\n"
					"3 - Low\n\n";

				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 3 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"high"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"medium"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"low"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}

			case 16: {	// userprofile weight

				retriever.AddField("userprofile weight");	

				cout << "\nWhat weight (in kilograms) would you like to search for?\n";

				cout << ">> ";
				string weight = "";
				cin >> weight;

				int minWeight = StringToInt(weight) - 5;
				int maxWeight = StringToInt(weight) + 5;

				string minWeightStr = IntToString(minWeight);
				string maxWeightStr = IntToString(maxWeight);

				cout << "Min: " << minWeightStr << endl;
				cout << "Max: " << maxWeightStr << endl;

				vector<QueryCondition> queryConditions;

				queryConditions.push_back(
					QueryCondition(
						"userprofile weight",
						QueryOperator::LessThan,
						maxWeightStr));

				queryConditions.push_back(
					QueryCondition(
						"userprofile weight",
						QueryOperator::GreaterThan,
						minWeightStr));

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 17: {	// userprofile height

				retriever.AddField("userprofile height");	

				cout << "\nWhat height (in meters) would you like to search for?\n";
				
				cout << ">> ";
				string height = "";
				cin >> height;

				float minHeight = StringToFloat(height) - (float)0.250;
				float maxHeight = StringToFloat(height) + (float)0.250;

				string minHeightStr = FloatToString(minHeight);
				string maxHeightStr = FloatToString(maxHeight);

				//cout << "Min: " << minHeightStr << endl;
				//cout << "Max: " << maxHeightStr << endl;

				vector<QueryCondition> queryConditions;

				queryConditions.push_back(
					QueryCondition(
						"userprofile height",
						QueryOperator::LessThan,
						maxHeightStr));

				queryConditions.push_back(
					QueryCondition(
						"userprofile height",
						QueryOperator::GreaterThan,
						minHeightStr));

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 18: {	// usercuisine Rcuisine

				retriever.AddField("usercuisine Rcuisine");	

				cout << "\nWhat cuisine preferences would you like to search for?\n";

				vector<string> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					if(userInput == ";")
						break;

					else
						optionsVec.push_back(userInput);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					queryConditions.push_back(
						QueryCondition(
							"usercuisine Rcuisine",
							QueryOperator::Equals,
							optionsVec[i]));
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::AND);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
			case 19: {	// userpayment Upayment

				retriever.AddField("userpayment Upayment");	

				cout << "\nWhat preferred method of payment would you like to search for?\n"
					"1 - Cash\n"
					"2 - Bank Debit Cards\n"
					"3 - MasterCard Eurocard\n"
					"4 - VISA\n"
					"5 - American Express\n\n";
				
				vector<int> optionsVec;
				string userInput = "";
				while(userInput != ";") {
					cout << ">> ";
					cin >> userInput;

					int userInputVerified = StringToInt(userInput);

					if(userInput == ";")
						break;
		
					else if(userInputVerified > 5 || userInputVerified < 1)
						cout << "\nInvalid option. Try again...\n\n";

					else
						optionsVec.push_back(userInputVerified);
				}

				vector<QueryCondition> queryConditions;
				for(unsigned int i=0; i<optionsVec.size(); i++) {
					switch(optionsVec[i]) {
					case 1:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"cash"));
						break;
					case 2:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"bank_debit_cards"));
						break;
					case 3:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"MasterCard-Eurocard"));
						break;
					case 4:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"VISA"));
						break;
					case 5:
						queryConditions.push_back(
							QueryCondition(
								"userprofile budget",
								QueryOperator::Equals,
								"American_Express"));
						break;
					}
				}

				QueryCondition conditionToStore = queryConditions[0];
				for(unsigned int i = 1; i < queryConditions.size(); i++)
					conditionToStore = QueryCondition(
											conditionToStore,
											queryConditions[i],
											QueryOperator::OR);

				retriever.AddQueryCondition(conditionToStore);
				break;
			}
		}
	}
}


void RestaurantSearch(vector<int> optionsVec, Retriever& retriever)
{
	retriever.AddQueryCondition(
		QueryCondition(
			"geoplaces2 placeID",
			QueryOperator::DoesNotEqual,
			"-10000"));

	for(unsigned int i=0; i<optionsVec.size(); i++) 
	{
		int queryOption = optionsVec[i];
		
		switch(queryOption)
		{			
			case 1:	{
				retriever.AddField("geoplaces2 latitude");
				retriever.AddField("geoplaces2 longitude");

					cout << "\nWhat location would you like to search for?\n";
					
					cout << "Max Latitude: \n";
					string maxLat = "";
					cin >> maxLat;
				
					cout << "Min Latitude: \n";
					string minLat = "";
					cin >> minLat;

					cout << "Max Longitude: \n";
					string maxLon = "";
					cin >> maxLon;

					cout << "Min Longitude: \n";
					string minLon = "";
					cin >> minLon;

					vector<QueryCondition> queryConditions;

					queryConditions.push_back(
						QueryCondition(
							"geoplaces2 latitude",
							QueryOperator::LessThan,
							maxLat));

					queryConditions.push_back(
						QueryCondition(
							"geoplaces2 latitude",
							QueryOperator::GreaterThan,
							minLat));

					queryConditions.push_back(
						QueryCondition(
							"geoplaces2 longitude",
							QueryOperator::LessThan,
							maxLon));

					queryConditions.push_back(
						QueryCondition(
							"geoplaces2 longitude",
							QueryOperator::GreaterThan,
							minLon));

					retriever.AddQueryCondition(
						QueryCondition(
							queryConditions,
							QueryOperator::AND));

					break;
					}
				
			case 2: {
						cout <<"\n What Restuarant would you want to search for?\n";						

						vector<string> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							if(userInput == ";")
								break;

							else
								optionsVec.push_back(userInput);
						}

						vector<QueryCondition> queryConditions;
				
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							queryConditions.push_back(
								QueryCondition(
									"geoplaces2 name",
									QueryOperator::Equals,
									optionsVec[i]));
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::AND);

						retriever.AddQueryCondition(conditionToStore);
						break;
						
					}

			case 3: {
						cout <<"\n What Address would you want to search for?\n";					
						
						vector<string> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							if(userInput == ";")
								break;

							else
								optionsVec.push_back(userInput);
						}

						vector<QueryCondition> queryConditions;
				
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							queryConditions.push_back(
								QueryCondition(
									"geoplaces2 address",
									QueryOperator::Equals,
									optionsVec[i]));
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::AND);

						retriever.AddQueryCondition(conditionToStore);
						break;
						
					}

			case 4: {
						cout <<"\n What kind of Alcohol Service would you want to search for?\n";
						cout << "1: No Alchohol\n";
						cout << "2: Wine or Beer\n";
						cout << "3: Full Bar \n";

						retriever.AddField("geoplaces2 alcohol");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 alcohol",
										QueryOperator::Equals,
										"No_Alcohol_Served"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 alcohol",
										QueryOperator::Equals,
										"Wine-Beer"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 alcohol",
										QueryOperator::Equals,
										"Full_Bar"));
								break;
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						break;
					}
					
			case 5: {
						cout << "\nWhat smoking preference would you like to search for?\n";
						cout << "1: None\n";
						cout << "2: Only at Bar\n";
						cout << "3: Premitted\n";
						cout << "4: Section\n";
						cout << "5: Not Premitted\n";
						
						retriever.AddField("geoplaces2 smoking_area");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 5 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 smoking_area",
										QueryOperator::Equals,
										"None"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 smoking_area",
										QueryOperator::Equals,
										"only_at_bar"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 smoking_area",
										QueryOperator::Equals,
										"premitted"));
									break;
							case 4:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 smoking_area",
										QueryOperator::Equals,
										"sectoin"));
									break;
							case 5:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 smoking_area",
										QueryOperator::Equals,
										"not_permitted"));
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						break;
					}

			case 6: {
						cout << "\n What kind of dress code would you like to search for?\n";
						cout << "1: informal\n";
						cout << "2: cascual\n";
						cout << "3: formal\n";

						retriever.AddField("geoplaces2 dress_code");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 dress_code",
										QueryOperator::Equals,
										"informal"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 dress_code",
										QueryOperator::Equals,
										"casual"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 dress_code",
										QueryOperator::Equals,
										"formal"));
									break;
							
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						break;
					}

			case 7: {
						cout << "\n What type of accessibility would you like to search for?\n";
						cout << "1: No Accessiblity\n";
						cout << "2: Completely\n";
						cout << "3: Partially\n";

						retriever.AddField("geoplaces2 accessibility");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 accessibility",
										QueryOperator::Equals,
										"no_accessibility"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 accessibility",
										QueryOperator::Equals,
										"completely"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 accessibility",
										QueryOperator::Equals,
										"partially"));
									break;							
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);
						break;
					}

			case 8: {
						cout << "\n What kind of price range would you like to search for?\n";
						cout << "1: Low\n";
						cout << "2: Medium\n";
						cout << "3: High\n";

						retriever.AddField("geoplaces2 price");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 price",
										QueryOperator::Equals,
										"low"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 price",
										QueryOperator::Equals,
										"medium"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 price",
										QueryOperator::Equals,
										"high"));
									break;
						
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						break;
					}
			
			case 9: {
						cout << "\n Would you like to search for restaurant with a website?\n";
						cout << "1: Yes\n";
						cout << "2: No\n";

						retriever.AddField("geoplaces2 url");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 2 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 url",
										QueryOperator::DoesNotEqual,
										"NULL"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 url",
										QueryOperator::Equals,
										"NULL"));
									break;
							
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);
						break;
					}

			case 10:{ 
						 cout << "\n What kind of Ambeince type would you like to search for?\n";
						 cout << "1: Familar\n";
						 cout << "2: Quiet\n";

						retriever.AddField("geoplaces2 Rambience");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) 
						{
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 Rambience",
										QueryOperator::Equals,
										"familar"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 Rambience",
										QueryOperator::Equals,
										"quiet"));
									break;							
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						 break;
					}

			case 11: {
						cout << "\n What kind of Restaurant Status would you like to search for?\n";
						cout << "1: Local\n";
						cout << "2: Franchise\n";

						retriever.AddField("geoplaces2 franchise");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 2 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 franchise",
										QueryOperator::Equals,
										"f"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 franchise",
										QueryOperator::Equals,
										"t"));
									break;							
						
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);

						break;
						
					 }

			case 12:{
						cout << "\n What kind of area are would you like to search for\n";
						cout << "1: Open\n";
						cout << "2: Closed\n";

						retriever.AddField("geoplaces2 area");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 2 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 area",
										QueryOperator::Equals,
										"open"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 area",
										QueryOperator::Equals,
										"closed"));
									break;							
						
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);						

						break;
					}

			case 13: {
						cout << "\n What kind of special servies would you like to search for?\n";
						cout << "1: None\n";
						cout << "2: Internet\n";
						cout << "3: Variety\n";

						retriever.AddField("geoplaces2 other_services");

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 3 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 other_services",
										QueryOperator::Equals,
										"none"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 other_services",
										QueryOperator::Equals,
										"Internet"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"geoplaces2 other_services",
										QueryOperator::Equals,
										"variety"));
									break;
						
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);						

						break;
					 }

			case 14: {
						cout << "\n What are the hours of operation would you like to search for?\n";
						cout << "From: \n";												

						retriever.AddField("chefmozhours4 openHour"); // MB ? 

						string from = "";
						cin >> from;			
						
						cout << "To: \n";
						string to = "";
						cin >> to;

						vector<QueryCondition> queryConditions;

						queryConditions.push_back(
							QueryCondition(
								"chefmozhours4 openHour",
								QueryOperator::LessThan,
								from));

						queryConditions.push_back(
							QueryCondition(
								"chefmozhours4 closeHour",
								QueryOperator::GreaterThan,
								to));

						

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::AND);

						retriever.AddQueryCondition(conditionToStore);

						break;
						}


			case 15: {
						cout << "\n What cuisines would you like to search for?\n";
						
						retriever.AddField("usercusine Rcuisine"); 

						vector<string> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							if(userInput == ";")
								break;

							else
								optionsVec.push_back(userInput);
						}

						vector<QueryCondition> queryConditions;
				
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							queryConditions.push_back(
								QueryCondition(
									"usercusine Rcuisine",
									QueryOperator::Equals,
									optionsVec[i]));
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);
						break;
						
					}

			case 16: {
						cout << "\n What method of payments would you like to search for?\n";
						cout << "1: Cash\n";
						cout << "2: VISA\n";
						cout << "3: MasterCard - EuroCard\n";
						cout << "4: American Express\n";
						cout << "5: Bank Debit Card\n";
						cout << "6: Checks\n";
						cout << "7: Discover Card\n";
						cout << "8: Carte Blanche\n";
						cout << "9: Diners_Club\n";					 
						cout << "10: Japan Credit Bureau\n";
						cout << "11: Gift Cerificates\n";

						retriever.AddField("chefmozaccepts Rpayment"); 
						
						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 11 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"cash"));
								break;
							case 2:{
										QueryCondition condition1 = QueryCondition(
												"chefmozaccepts Rpayment",
												QueryOperator::Equals,
												"VISA");
										QueryCondition condition2 = QueryCondition(
												"chefmozaccepts Rpayment",
												QueryOperator::Equals,
												"Visa");
										QueryCondition condition = QueryCondition(
											condition1,
											condition2,
											QueryOperator::OR);

										queryConditions.push_back(condition);

											break;
								   }
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"MasterCard-Eurocard"));
									break;
							case 4:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"American_Express"));
								break;
							case 5:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"bank_debit_cards"));
									break;
							case 6:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"checks"));
									break;
							
							case 7:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"Discover"));
									break;

							case 8:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"Carte_Blanche"));
								break;
							case 9:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"Diners_Club"));
									break;
							case 10:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"Japan_Credit_Bureau"));
									break;
							case 11:
								queryConditions.push_back(
									QueryCondition(
										"chefmozaccepts Rpayment",
										QueryOperator::Equals,
										"gift_certificates"));
								break;							
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);	

						break;
					 }

			case 17: {
						cout << "\n What kind of parking options would you like to search for?\n";
						cout << "1: Yes\n";
						cout << "2: None\n";
						cout << "3: Public\n"; 
						cout << "4: Valet Parking\n";
						cout << "5: Street\n";
						cout << "6: Free \n";
						cout << "7: Validated Parking\n";

						retriever.AddField("chefmozparking parking_lot"); 

						vector<int> optionsVec;
						string userInput = "";
						while(userInput != ";") {
							cout << ">> ";
							cin >> userInput;

							int userInputVerified = SyntaxCheck(userInput);

							if(userInput == ";")
								break;
		
							else if(userInputVerified > 7 || userInputVerified < 1)
								cout << "\nInvalid option. Try again...\n\n";

							else
								optionsVec.push_back(userInputVerified);
						}

						vector<QueryCondition> queryConditions;
						for(unsigned int i=0; i<optionsVec.size(); i++) {
							switch(optionsVec[i]) {
							case 1:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"yes"));
								break;
							case 2:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"none"));
									break;
							case 3:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"public"));
									break;
							case 4:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"valet_parking"));
								break;
							case 5:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"street"));
									break;
							case 6:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"free"));
									break;
							
							case 7:
								queryConditions.push_back(
									QueryCondition(
										"chefmozparking parking_lot",
										QueryOperator::Equals,
										"validated_parking"));
									break;
							}
						}

						QueryCondition conditionToStore = queryConditions[0];
						for(unsigned int i = 1; i < queryConditions.size(); i++)
							conditionToStore = QueryCondition(
													conditionToStore,
													queryConditions[i],
													QueryOperator::OR);

						retriever.AddQueryCondition(conditionToStore);	

						break;	
					 }
				}
		}
}


// Utility Function
int SyntaxCheck(string str) {
	for(unsigned int i = 0; i < str.size(); i++) {
		if(!isdigit(str[i])) {
			return -1;
		}
	}

	stringstream stream(str);
	int num;
	stream >> num;
	return num;
}