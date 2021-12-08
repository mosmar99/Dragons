#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "database.h"
#include "dragon.h"

// Loads the content in .txt file into the database
void loadDatabase(char *, Database *);

// Stores the database in a chosen file
void saveDatabase(char *, Database *);

#endif