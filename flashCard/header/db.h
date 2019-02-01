#ifndef HEADERS_DB_H_
#define HEADERS_DB_H_

#include <iostream>
#include <iomanip>
#include <sqlite3.h>

class DBManager {
	sqlite3* database;
	DBManager();
	~DBManager();

	/* Initializer methods */
	bool openDatabase();
	bool createTables();

	/* Callback functions for sqlite3_exec */
	static int setManagerCallback(void*, int, char**, char**);
	static int setCallback(void*, int, char**, char**);
public:
	static DBManager& instance();
	void createSet();
	void displayAllSets();
	void displaySet(std::string);
	DBManager(const DBManager&) = delete;
	void operator =(const DBManager&) = delete;
};

#endif /* HEADERS_DB_H_ */
