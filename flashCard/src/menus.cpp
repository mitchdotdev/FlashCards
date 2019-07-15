#include "../header/menus.h"

void mainMenu() {
	showTitle();
	// Main menu
	DBManager::instance().setStateID(0);
	std::cout << "\n\n"
				 "[ 0 ] Exit\n"
				 "[ 1 ] View sets\n"
				 "[ 2 ] Create a set\n"
				 ": ";

	switch (menuInput(3)) {
	//clearScreen();

		case 0: {
			std::exit(0);
			break;
		}
		case 1: {
			showTitle();
			// View sets
			DBManager::instance().displayAllSets();
			setMenu();
			break;
		}
		case 2: {
			// Create a set
			std::string setName;
			std::cout << "\n\n"
						 "Enter the name of the new set: ";
			std::getline( std::cin, setName );
			if ( DBManager::instance().createSet(setName) == 0 ) {
				clearScreen();
				std::cout << "SET ADDED!\n\n";
				sleep(1);
				mainMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				mainMenu();
			}
			break;
		}
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
		case 0: {
			// Back
			mainMenu();
			break;
		}
		case 1: {
			// Edit set (set stateid)
			std::string id;
			std::cout << "\n"
						 "Enter the set ID: ";
			std::getline( std::cin, id );
			showTitle();
			if ( DBManager::instance().displaySet(id) == 0 ) {
				DBManager::instance().setStateID(std::stoi(id));
				cardMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				mainMenu();
			}
			break;
		}

		case 2: {
			// Delete set (set stateid)
			std::string id;
			std::cout << "\n"
						 "Enter the set ID: ";
			std::getline( std::cin, id );
			if ( DBManager::instance().deleteSet(id) == 0 ) {
				clearScreen();
				std::cout << "SET DELETED!\n\n";
				sleep(1);
				mainMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				mainMenu();
			}
			break;
		}
	}
}

void cardMenu() {
	// Card menu
	std::cout << "\n\n"
				 "[ 0 ] Back\n"
				 "[ 1 ] Add card\n"
				 "[ 2 ] Edit word\n"
				 "[ 3 ] Edit definition\n"
				 "[ 4 ] Delete card\n"
				 ": ";

	switch (menuInput(5)) {

		case 0: {
			// Back
			showTitle();
			DBManager::instance().displayAllSets();
			setMenu();
			break;
		}

		case 1: {
			std::string newWord;
			std::string newDefinition;
			std::cout << "\n\n"
						 "Enter the word of the flashcard: ";
			std::getline( std::cin, newWord);
			std::cout << "Enter the definition of the flashcard: ";
			std::getline( std::cin, newDefinition );

			if ( DBManager::instance().addFlashcard(newWord, newDefinition) == 0 ) {
				clearScreen();
				std::cout << "CARD ADDED!\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			}
			break;
		}

		case 2: {
			// Edit word
			std::string oldWord;
			std::string newWord;

			std::cout << "\n\n"
						 "Enter the word of the flashcard to edit: ";
			std::getline( std::cin, oldWord );
			std::cout << "Enter the new word for the flashcard: ";
			std::getline( std::cin, newWord );

			if ( DBManager::instance().editWord(oldWord, newWord) == 0 ) {
				clearScreen();
				std::cout << "CARD EDITED!\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			}
			break;
		}

		case 3: {
			// Edit definition
			std::string word;
			std::string newDefinition;

			std::cout << "\n\n"
						 "Enter the word of the flashcard to edit: ";
			std::getline( std::cin, word );
			std::cout << "Enter the new definition for the flashcard: ";
			std::getline( std::cin, newDefinition );

			if ( DBManager::instance().editDefinition(word, newDefinition) == 0 ) {
				clearScreen();
				std::cout << "CARD EDITED!\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			}
			break;
		}

		case 4: {
			// Delete card
			std::string word;

			std::cout << "\n\n"
						 "Enter the word of the flashcard to delete: ";
			std::getline( std::cin, word );

			if ( DBManager::instance().deleteFlashcard(word) == 0 ) {
				clearScreen();
				std::cout << "CARD DELETED!\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			} else {
				clearScreen();
				std::cerr << ". . . ERROR OCCURRED . . .\n\n";
				sleep(1);
				showTitle();
				DBManager::instance().displaySet(std::to_string(DBManager::instance().getStateID()));
				cardMenu();
			}
			break;
		}
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

void showTitle() {
	clearScreen();
	std::cout << " _______  ___      _______  _______  __   __  _______  _______  ______    ______   _______ \n"
				 "|       ||   |    |   _   ||       ||  | |  ||       ||   _   ||    _ |  |      | |       |\n"
				 "|    ___||   |    |  |_|  ||  _____||  |_|  ||       ||  |_|  ||   | ||  |  _    ||  _____|\n"
				 "|   |___ |   |    |       || |_____ |       ||       ||       ||   |_||_ | | |   || |_____ \n"
				 "|    ___||   |___ |       ||_____  ||       ||      _||       ||    __  || |_|   ||_____  |\n"
				 "|   |    |       ||   _   | _____| ||   _   ||     |_ |   _   ||   |  | ||       | _____| |\n"
				 "|___|    |_______||__| |__||_______||__| |__||_______||__| |__||___|  |_||______| |_______|";
}
