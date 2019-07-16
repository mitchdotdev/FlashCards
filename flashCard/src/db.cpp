 #include "../headers/db.h"

DBManager::DBManager() {
	// Initialize stateID
	this->stateID = 0;

	// If database successfully opens, create base tables
	if(openDatabase())
        createTables(); 
}

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
					   "`ID`	INTEGER PRIMARY KEY AUTOINCREMENT, "
					   "`Name`	TEXT UNIQUE )";

	// Creating table to hold the flashcards that reference the id of the set they belong to
	std::string sql2 = "CREATE TABLE `Sets` ("
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

int DBManager::createSet(std::string setName) {
	// Construct query
	std::string query = "INSERT INTO `Set_Manager` (`Name`) "
						"VALUES (\'" + setName + "\')";

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::deleteSet(std::string id) {
	// Construct query
	std::string query = "DELETE FROM `Set_Manager` "
						"WHERE `ID` = " + id;

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::addFlashcard(std::string word, std::string definition) {
	// Construct query
	std::string query = "INSERT INTO `Sets` (`word`, `definition`, `setID`) "
						"VALUES (\'" + word + "\', \'" + definition + "\', " + std::to_string(this->stateID) + ") ";

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::deleteFlashcard(std::string word) {
	// Construct query
	std::string query = "DELETE FROM `Sets` "
						"WHERE `word` = \'" + word + "\'";

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::editWord(std::string oldWord, std::string newWord) {
	// Construct query
	std::string query = "UPDATE `Sets` "
						"SET `word` = \'" + newWord + "\' "
						"WHERE `word` = \'" + oldWord + "\' AND `setID` = " + std::to_string(this->getStateID());

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
}

int DBManager::editDefinition(std::string word, std::string newDefinition) {
	// Construct query
	std::string query = "UPDATE `Sets` "
						"SET `definition` = \'" + newDefinition + "\' "
						"WHERE `word` = \'" + word + "\' AND `setID` = " + std::to_string(this->getStateID());

	// Execute query
	return sqlite3_exec(database, query.c_str(), NULL, NULL, NULL);
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
	std::cout << std::setw(7) << std::left << "\nID" << "Set Name\n______________\n";

	std::string query = "SELECT * FROM `Set_Manager` ORDER BY `ID`";

	/* Execute query and display results via callback function */
	sqlite3_exec(database, query.c_str(), setManagerCallback, NULL, NULL);

}

int DBManager::displaySet(std::string choice) {
	std::cout << std::setw(13) << std::left << "\nWord" << "Definition\n________________________\n";

	std::string query = "SELECT `word`, `definition` FROM `Sets` WHERE `setID` = " + choice + " ORDER BY `word`";

	/* Execute query and display results via callback function */
	return sqlite3_exec(database, query.c_str(), setCallback, NULL, NULL);
}

void DBManager::setStateID(int state) {
	this->stateID = state;
}

int DBManager::getStateID() {
	return this->stateID;
}

DBManager& DBManager::instance() {
	// Instantiate and return static database object
	static DBManager DB;
	return DB;
}
