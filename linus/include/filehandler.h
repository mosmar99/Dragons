#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

#include "database.h"

// Loads the content in .txt file into the database
void loadDatabase(const char *const, Database *const);

// Stores the database in a chosen file
void saveDatabase(const char *const, const Database *const);

#endif