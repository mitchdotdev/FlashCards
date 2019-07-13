#ifndef HEADERS_DB_H_
#define HEADERS_DB_H_

#include <iostream>
#include <iomanip>
#include <sqlite3.h>

class DBManager {
	// sqlite3 database object
	sqlite3* database;
	// Constructor
	DBManager();
	// Destructor
	~DBManager();

	/* Initializer methods */
	bool openDatabase();
	bool createTables();

	/* Callback functions for sqlite3_exec */
	static int setManagerCallback(void*, int, char**, char**);
	static int setCallback(void*, int, char**, char**);
public:
	/*
	 * Creates static instance of database
	 */
	static DBManager& instance();
	/*
	 * Selects the correct database entry
	 */
	int dbSelect(std::string, int);
	/*
	 * Creates a new flashcard set
	 */
	void createSet(std::string);
	/*
	 * Displays a list of all flashcard sets
	 */
	void displayAllSets();
	/*
	 * Displays the contents of a flashcard set
	 */
	void displaySet(std::string);

	/* Delete copy constructor and assignment operator */
	DBManager(const DBManager&) = delete;
	void operator =(const DBManager&) = delete;
};

#endif /* HEADERS_DB_H_ */
