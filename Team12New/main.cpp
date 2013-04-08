#include "UI.h"
#include "FileReader.h"

int main() {
	string userInput = "";
	int quit = 0;

	Database database = Database();
	LoadDataBase(database);

	cout << "WELCOME TO THE RESTAURANT & CONSUMER DATABASE!";	
	
	while(!quit) {
		Retriever RETRIEVER = Retriever();
		//UserPlaceConnection USERPLACECONNECTION = UserPlaceConnection();

		cout << Welcome << endl;
		cout << ">> ";
		cin >> userInput;
		int userInputVerified = StringToInt(userInput);

		if(userInput == "q")
			quit = 1;

		else if(userInputVerified == -1)
			cout << "Not a valid option...\n";
		
		else
			DetermineInitialDecision(userInputVerified, RETRIEVER);
		
		RETRIEVER.LinkDatabase(database);
		Table result = RETRIEVER.GetData();
		PrintTable(result);
	}

	cout << "Exiting database...";
	return 0;
}