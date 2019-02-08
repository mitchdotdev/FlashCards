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

	while(!exit) {
		choice = menu(MAIN_MENU);
		switch(choice) {
		case 0:
			std::cout << "bye";
			exit = true;
			break;
		case 1:
			choice = menu(SUB_MENU1);
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
