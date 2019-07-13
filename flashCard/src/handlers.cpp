#include "../header/handlers.h"

void init() {

	std::cout << " _______  ___      _______  _______  __   __  _______  _______  ______    ______   _______ \n"
				 "|       ||   |    |   _   ||       ||  | |  ||       ||   _   ||    _ |  |      | |       |\n"
				 "|    ___||   |    |  |_|  ||  _____||  |_|  ||       ||  |_|  ||   | ||  |  _    ||  _____|\n"
				 "|   |___ |   |    |       || |_____ |       ||       ||       ||   |_||_ | | |   || |_____ \n"
				 "|    ___||   |___ |       ||_____  ||       ||      _||       ||    __  || |_|   ||_____  |\n"
				 "|   |    |       ||   _   | _____| ||   _   ||     |_ |   _   ||   |  | ||       | _____| |\n"
				 "|___|    |_______||__| |__||_______||__| |__||_______||__| |__||___|  |_||______| |_______|\n\n";
	// Instantiate database
	DBManager::instance();
}

void menuController() {
	int choice;
	bool exit = false;

	// Get menu choice from the user
	std::cout << "\nMAIN MENU:\n_ _ _\n\n[ 0 ] EXIT\n[ 1 ] View your sets\n[ 2 ] Create a set\n: ";
	choice = menuInput(MAIN_MENU);

	while(!exit) {
		switch(choice) {
		// case 0: Exits the program
		case 0:
			std::cout << "bye";
			exit = true;
			break;
		// case 1: Displays the list of available sets to view, upon selection will display the selected set
		case 1:
			// Output all sets
			DBManager::instance().displayAllSets();
			std::cout << "\nEnter the ID# of the set you\'d like to view: ";

			// If user selects a valid set ID, display the sets contents
			if(dbInput(SETS) != -1)
				DBManager::instance().displaySet(std::to_string(choice));
			else
				std::cout << "It don\'t exist bruv\n\n";
			exit = true;
			break;
		// case 2: Will create a new set
		case 2:
			std::string setName;
			std::cout << "Enter the name of the new set: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, setName);

			// Create new set with user generated name
			DBManager::instance().createSet(setName);
			exit = true;
			break;

		}
	}
}

int menuInput(int numOfChoices) {
	bool exit = false;
	int choice;

	// Error handles until a valid choice is selected from the given menu
	while(!exit) {
		std::cin >> choice;
		if(std::cin.fail() || choice < 0 || choice >= numOfChoices) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "ERROR . . . Please only enter one of the choice displayed\n: ";
		} else
			exit = true;
	}

	return choice;
}

int dbInput(int queryType) {
	int choice;
	bool exit = false;

	// Error handles until a valid choice is selected from the given menu
	while(!exit) {
		std::cin >> choice;
		if(std::cin.fail() || choice < 0) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "ERROR . . . Please only enter one of the choice displayed\n: ";
		} else
			exit = true;
	}

	switch(queryType) {
	// case 0: Queries a set by ID
	case 0:
		std::string query = "SELECT `ID` "
							"FROM `Set_Manager` "
							"WHERE `ID` = ";
		choice = DBManager::instance().dbSelect(query, choice);
		break;
	}

	return choice;
}
