#ifndef _DATABASE_H
#define _DATABASE_H

/*
File: database.h.h
Description: 
This file contains the interface of many functions to handle
a database and its properties
*/

#include "dragon.h"
#include <stdbool.h>

// Error strings used in error messages
#define ERROR_STRING_DATABASE_EMPTY "Error: no dragons in database"

// The initial capacity of the database
#define INITIAL_CAPACITY 10

// If the database gets full, its size multiplies with this factor
#define GROWTH_FACTOR 2

// Maximum number (minus 1) of characters allowed in name of database
#define MAX_FILENAME 50

// The default value / terminator for the dragon indexes array
#define SENTINEL -1

typedef struct Database
{
    Dragon *dragons;       // array of dragons
    unsigned int capacity; // current maximum capacity
    unsigned int size;     // current number of dragons stored in array
    unsigned int nextId;   // next available unique id
} Database;

// Creates an empty database on heap and returns pointer to it
Database *createDatabase();

// Increases the database capacity according to GROWTH_FACTOR
// Paramter: (a database)
void expandCapacity(Database *const db);

// Frees the memory occupied by a Database
// Parameter: (a database)
void destroyDatabase(Database *);

// Search database for dragon/s by name or ID
// Returns an array of indexes of dragon/s that matches the identifier
// The default value is SENTINEL
// Paramters: (a database), (an identifier as either ID or name)
int *searchForDragon(const Database *const db, const char *const identifier);

// Gather min and max values for fierceness, #volant and #non-volant
// Parameters:(a database), (mininimum fierceness), (maximum fierceness), (number of volant), (number of non-volant)
void getDatabaseInfo(const Database *const db, size_t *const minF, size_t *const maxF, size_t *const nV, size_t *const nNonV);

// Finds the array index given a dragon's id
// Returns -1 if not found
// Paramteters: (a database), (a dragon's id)
int idToIndex(const Database *const db, const unsigned int id);

// Delete a dragon by array index
// Parameters: (a database), (the array-index of a dragon)
void doDeleteDragon(Database *const db, int ix);

// Sort the database in ascending order by name or id
// Parameters: (a database), (true = by name, false = by id)
void sortDragons(Database *const db, const bool);

// Checks if the selected ID is present in the database AND indexes array
// Parameters: (a database), (an int array with array indexes of dragon/s), (an ID to check)
bool dragonsHasID(const Database *const db, const unsigned int *const ixs, unsigned int id);

// Used to free the indexes array created by searchForDragon()
// Parameters: (the array)
void freeIxArray(int *ixArray);

#endif