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

	// Current set ID
	int stateID;

	/* Initializer methods */
	bool openDatabase();
	bool createTables();

	/* Callback functions for sqlite3_exec */
	static int setManagerCallback(void*, int, char**, char**);
	static int setCallback(void*, int, char**, char**);
public:
	// Creates static instance of database
	static DBManager& instance();

	// Creates a new flashcard set
	int createSet(std::string);

	// Deletes a flashcard set
	int deleteSet(std::string);

	// Adds a flashcard to a set
	int addFlashcard(std::string, std::string);

	// Deletes a flashcard from a set
	int deleteFlashcard(std::string);

	// Edits the word on a flashcard
	int editWord(std::string, std::string);

	// Edits the definition on a flashcard
	int editDefinition(std::string, std::string);

	// Displays a list of all flashcard sets
	void displayAllSets();

	// Displays the contents of a flashcard set
	int displaySet(std::string);

	// Sets the ID of the current Set
	void setStateID(int);

	// Gets the ID of the current Set
	int getStateID();

	/* Delete copy constructor and assignment operator */
	DBManager(const DBManager&) = delete;
	void operator =(const DBManager&) = delete;
};

#endif /* HEADERS_DB_H_ */
