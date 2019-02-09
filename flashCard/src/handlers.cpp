#include "../header/handlers.h"

void init() {

	std::cout << " _______  ___      _______  _______  __   __  _______  _______  ______    ______   _______ \n"
				 "|       ||   |    |   _   ||       ||  | |  ||       ||   _   ||    _ |  |      | |       |\n"
				 "|    ___||   |    |  |_|  ||  _____||  |_|  ||       ||  |_|  ||   | ||  |  _    ||  _____|\n"
				 "|   |___ |   |    |       || |_____ |       ||       ||       ||   |_||_ | | |   || |_____ \n"
				 "|    ___||   |___ |       ||_____  ||       ||      _||       ||    __  || |_|   ||_____  |\n"
				 "|   |    |       ||   _   | _____| ||   _   ||     |_ |   _   ||   |  | ||       | _____| |\n"
				 "|___|    |_______||__| |__||_______||__| |__||_______||__| |__||___|  |_||______| |_______|\n\n";
	DBManager::instance();
}

void menuController() {
	int choice;
	bool exit = false;

	std::cout << "\nMAIN MENU:\n_ _ _\n\n[ 0 ] EXIT\n[ 1 ] View your sets\n[ 2 ] Create a set\n: ";
	choice = validateInput(3);

	while(!exit) {
		switch(choice) {
		case 0:
			std::cout << "bye";
			exit = true;
			break;
		case 1:
			//choice = menu(SUB_MENU1);
			DBManager::instance().displayAllSets();
			exit = true;
			break;
		case 2:
			DBManager::instance().createSet();
			exit = true;
			break;

		}

	}

}

int validateInput(int numOfChoices) {
	bool exit = false;
	int choice;

	std::cin >> choice;
	while(!exit) {
		if(std::cin.fail() || choice < 0 || choice > numOfChoices ) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "ERROR . . . Please only enter one of the choice displayed\n: ";
		} else
			exit = true;
	}

	return choice;
}
