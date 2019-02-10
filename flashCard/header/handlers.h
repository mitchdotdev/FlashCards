#ifndef HANDLERS_H_
#define HANDLERS_H_
#define SETS 0
#define MAIN_MENU 3

#include "db.h"
#include "set.h"

void init();
void menuController();
int menuInput(int);
int dbInput(int);

#endif /* HANDLERS_H_ */
