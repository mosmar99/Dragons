#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

/*
File: filehandler.h
Description:
This file contains the interface of handling the loading and saving 
the database as a .txt file
*/

#include "database.h"

// Error strings used as error messages
#define ERROR_STRING_DATABASE_OPEN "Error: failed to open"

// Loads the content in .txt file into the database
// Parameters: (the full path to a .txt file), (a database)
// if the .txt path is NULL, it will use the last known path
void loadDatabase(const char *const str, Database *const db);

// Stores the database in a chosen file
// Parameters: (the full path to a .txt file), (a database)
// if the .txt path is NULL, it will use the last known path
void saveDatabase(const char *const str, const Database *const db);

#endif