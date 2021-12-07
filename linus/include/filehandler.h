#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

#include <assert.h>
#include <stdbool.h>
#include "database.h"
#include "dragon.h"

#define MAX_COLOUR_NAME 25

// Loads the content in .txt file into the database
void loadDatabase(char *, Database *);

// Stores the database in a chosen file
void saveDatabase(char *, Database *);

#endif