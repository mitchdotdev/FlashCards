#ifndef HANDLERS_H_
#define HANDLERS_H_
#define SETS 0
#define MAIN_MENU 3

#include "db.h"
#include "set.h"

/*
 * Outputs application title and initializes a single instance of the DBManager
 */
void init();
/*
 * Outputs application menus and delegates user input
 */
void menuController();
/*
 * Error checks and validates user input
 */
int menuInput(int);
/*
 * Error checks and validates user input for the database and delegates queries
 */
int dbInput(int);

#endif /* HANDLERS_H_ */
