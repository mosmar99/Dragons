#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

/*
File: filehandler.h
Description:
This file contains the interface of handling the loading and saving of a database as a .txt file
*/

#include "database.h"

// Loads the content in .txt file into the database
// Parameters: (the relative path to a .txt file), (a database)
// if the .txt path is NULL, it will use the last known path
void loadDatabase(const char *const str, Database *const db);

// Stores the database in a chosen .txt file
// Parameters: (the relative path to a .txt file), (a database)
// if the .txt path is NULL, it will use the last known path
void saveDatabase(const char *const str, const Database *const db);

#endif