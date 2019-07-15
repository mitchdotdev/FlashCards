#ifndef HEADERS_MENUS_H_
#define HEADERS_MENUS_H_

#include <sstream>
#include <ios>
#include <unistd.h>
#include <term.h>

#include "db.h"

// Clears console screen and prints title
void showTitle();

// Displays and delegates main menu tasks
void mainMenu();

// Displays and delegates set menu tasks
void setMenu();

// Displays and delegates card menu tasks
void cardMenu();

// Handles all menu input
int menuInput(int menuChoices);

// Clears console screen
void clearScreen();

#endif /* HEADERS_MENUS_H_ */
