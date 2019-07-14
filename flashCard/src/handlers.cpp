#include "../header/handlers.h"

void init() {
	// Instantiate database
	DBManager::instance();

	mainMenu();
}

void mainMenu() {
	std::cout << " _______  ___      _______  _______  __   __  _______  _______  ______    ______   _______ \n"
				 "|       ||   |    |   _   ||       ||  | |  ||       ||   _   ||    _ |  |      | |       |\n"
				 "|    ___||   |    |  |_|  ||  _____||  |_|  ||       ||  |_|  ||   | ||  |  _    ||  _____|\n"
				 "|   |___ |   |    |       || |_____ |       ||       ||       ||   |_||_ | | |   || |_____ \n"
				 "|    ___||   |___ |       ||_____  ||       ||      _||       ||    __  || |_|   ||_____  |\n"
				 "|   |    |       ||   _   | _____| ||   _   ||     |_ |   _   ||   |  | ||       | _____| |\n"
				 "|___|    |_______||__| |__||_______||__| |__||_______||__| |__||___|  |_||______| |_______|";
	// Main menu
	std::cout << "\n\n"
				 "[ 0 ] Exit\n"
				 "[ 1 ] View sets\n"
				 "[ 2 ] Create a set\n"
				 ": ";

	switch (menuInput(3)) {
	clearScreen();

	case 0:
		std::exit(0);
		break;

	case 1:
		// View sets
		DBManager::instance().displayAllSets();
		setMenu();
		break;

	case 2:
		// Create a set
		break;
	}
}

void setMenu() {
	// Set menu
	std::cout << "\n\n"
				 "[ 0 ] Back\n"
				 "[ 1 ] Edit set\n"
				 "[ 2 ] Delete set\n"
				 ": ";

	switch (menuInput(3)) {
	clearScreen();

	case 0:
		// Back
		mainMenu();
		break;

	case 1:
		// Edit set
		break;

	case 2:
		// Delete set
		break;
	}
}

int menuInput(int menuChoices) {
	std::string input;
	int choice;

	while (true) {
		std::getline( std::cin, input );
		std::istringstream convert (input);
		convert >> choice;

		if ( convert.fail() || choice < 0 || choice >= menuChoices )
			std::cout << "\n\n. . . ERROR . . .\n: ";
		else
			return choice;
	}
}

void clearScreen() {
	 if (!cur_term) {
	    int result;
	    setupterm( NULL, STDOUT_FILENO, &result );
	    if (result <= 0) return;
	 }

	  putp( tigetstr( "clear" ) );
}
