#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

#include "database.h"

// Loads the content in .txt file into the database
void loadDatabase(char *, Database *);

// Stores the database in a chosen file
void saveDatabase(char *, Database *);

#endif