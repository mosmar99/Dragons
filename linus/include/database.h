#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdbool.h>
#include "dragon.h"

// The initial capacity of the database
#define INITIAL_CAPACITY 10

// If the database gets full, its size multiplies with this growth factor
#define GROWTH_FACTOR 2

// Maximum number (minus 1) of characters allowed in name of database
#define MAX_FILENAME 50

#define SENTINEL -1

// Error strings used as error messages
#define ERROR_STRING_DATABASE_EMPTY "Error: no dragons in database\n"

typedef struct Database
{
    Dragon *dragons;       // array of dragons
    unsigned int capacity; // current maximum capacity
    unsigned int size;     // current number of dragons stored in array
    unsigned int nextId;   // next available unique id
} Database;

// Creates an empty database on heap and returns pointer to it
Database *createDatabase();

// Grows the capacity according to GROWTH_FACTOR
// Paramter: (a database)
void expandCapacity(Database *const);

// Frees the RAM memory occupied by a Database
// Parameter: (a database)
void destroyDatabase(Database *);

// Search database for dragon/s by name or ID
// Returns an array of indexes of dragon/s that matches the identifier
// If no dragons are found, first (and all) element will be -1
// Paramters: (a database), (an identifier as either ID or name)
int *searchForDragon(const Database *const, const char *const);

// Gather min and max values for fierceness, #volant and #non-volant
// Parameters:(a database), (mininimum fierceness), (maximum fierceness), (number of volant), (number of non-volant)
void getDatabaseInfo(const Database *const, size_t *const, size_t *const, size_t *const, size_t *const);

// Finds the array index given a dragon's id
// Returns -1 if not found
// Paramteters: (a database), (a dragon's id)
int idToIndex(const Database *const, const unsigned int *const);

// Delete a dragon by array index
// Parameters: (a database), (the array-index of a dragon)
void doDeleteDragon(Database *const db, int ix);

// Sort the database in ascending order by name or id
// Parameters: (a database), (bool = true by name, bool = false by id)
void sortDragons(Database *const, const bool);

// Checks if the selected ID is present in the database
// Parameters: (a database), (an int array with array indexes of dragon/s), (an ID to check)
bool dragonsHasID(const Database *const db, const unsigned int *const ixs, unsigned int id);

// Allocates memory for a dragon's name at a certain array index
// Parameters: (a database), (the name for new dragon), (the array index of the dragon)
void createName(Database *const db, const char *const name, const unsigned int ix);

// Used to free the integer array created by searchForDragon()
// Parameters: (the array)
void freeIntegerArray(int *array);

#endif