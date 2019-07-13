 #include "../header/db.h"

// Constructor
DBManager::DBManager() {
	// If database successfully opens, create base tables
	if(openDatabase())
		createTables();
}

// Destructor
DBManager::~DBManager() { sqlite3_close(database); }

bool DBManager::openDatabase() {
	bool success;
	// If database opens unsuccessfully return false
	if(sqlite3_open("tst.db", &database))
		success = false;
	// Else return true
	else
		success = true;

	return success;
}

bool DBManager::createTables() {
	bool success;
	int exec1;
	int exec2;

	// Creating table to hold the name and id of all of the sets of flashcards
	std::string sql1 = "CREATE TABLE `Set_Manager` ("
					   "`ID`	INTEGER AUTOINCREMENT, "
					   "`Name`	TEXT UNIQUE, "
					   "PRIMARY KEY(`ID`) )";

	// Creating table to hold the flashcards that reference the id of the set they belong to
	std::string sql2 = "CREATE TABLE `Set` ("
					   "`word`	TEXT, "
					   "`definition`	TEXT, "
					   "`setID`	INTEGER, "
					   "FOREIGN KEY(`setID`) REFERENCES `Set_Manager`(`ID`) )";

	/* Execute both table queries */
	exec1 = sqlite3_exec(database, sql1.c_str(), NULL, NULL, NULL);
	exec2 = sqlite3_exec(database, sql2.c_str(), NULL, NULL, NULL);

	// If queries executed successfully return true
	if( (exec1 == SQLITE_OK || exec1 == 1) && (exec2 == SQLITE_OK || exec2 == 1) )
		success = true;
	// Else return false
	else
		success = false;

	return success;
}

int DBManager::dbSelect(std::string query, int choice) {
	query = query + std::to_string(choice);

    sqlite3_stmt *stmt;
    int result;

    int rc = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("error: %s\n", sqlite3_errmsg(database));
        // or throw an exception
        return -1;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        printf("error: %s\n", sqlite3_errmsg(database));
        // or throw an exception
        sqlite3_finalize(stmt);
        return -1;
    }

    if (rc == SQLITE_DONE) // no result
        result = -1;
    else if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) // result is NULL
        result = -1;
    else { // some valid result
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return result;
}

void DBManager::createSet(std::string setName) {
	// Construct query
	std::string query = "INSERT INTO `Set_Manager` (`Name`) "
						"VALUES (\'" + setName + "\')";

	// Execute query
	sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::setManagerCallback(void* data, int argc, char** argv, char** colName) {

	for(int i = 0; i < argc; ++i)
		std::cout << std::setw(6) << std::left << (argv[i] ? argv[i] : "NULL");

	std::cout << '\n';
	return 0;
}

int DBManager::setCallback(void* data, int argc, char** argv, char** colName) {

	for(int i = 0; i < argc; ++i)
		std::cout << std::setw(12) << std::left << (argv[i] ? argv[i] : "NULL");

	std::cout << '\n';
	return 0;
}

void DBManager::displayAllSets() {
	std::string query = "SELECT * FROM `Set_Manager` ORDER BY `ID`";

	/* Execute query and display results via callback function */
	std::cout << std::setw(7) << std::left << "\nID" << "Set Name\n______________\n";
	sqlite3_exec(database, query.c_str(), setManagerCallback, NULL, NULL);

}

void DBManager::displaySet(std::string choice) {
	std::string query = "SELECT `word`, `definition` FROM `Set` WHERE `setID` = " + choice + " ORDER BY `word`";

	/* Execute query and display results via callback function */
	std::cout << std::setw(13) << std::left << "\nWord" << "Definition\n________________________\n";
	sqlite3_exec(database, query.c_str(), setCallback, NULL, NULL);
}

DBManager& DBManager::instance() {
	// Instantiate and return static database object
	static DBManager DB;
	return DB;
}
