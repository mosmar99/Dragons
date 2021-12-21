#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

#include "database.h"

#define ERROR_STRING_DATABASE_OPEN "Error: failed to open"

// Loads the content in .txt file into the database
// Parameters: (the full path to a .txt file), (a database)
void loadDatabase(const char *const str, Database *const db);

// Stores the database in a chosen file
// Parameters: (the full path to a .txt file), (a database)
void saveDatabase(const char *const str, const Database *const db);

#endif