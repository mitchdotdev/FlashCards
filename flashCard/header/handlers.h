#ifndef HANDLERS_H_
#define HANDLERS_H_
#define SETS 0
#define MAIN_MENU 3

#include <sstream>
#include <ios>
#include <unistd.h>
#include <term.h>

#include "db.h"

void init();

void mainMenu();

void setMenu();

void cardMenu();

int menuInput(int menuChoices);

void clearScreen();

#endif /* HANDLERS_H_ */
