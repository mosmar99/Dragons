#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "dragon.h"

// The initial capacity of the database
#define INITIAL_CAPACITY 10

// If the database gets full, its size multiplies with this growth factor
#define GROWTH_FACTOR 2

// Maximum number (minus 1) of characters allowed in name of database
#define MAX_FILENAME 50

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
void expandCapacity(Database *const);

// Frees the RAM memory occupied by a Database
void destroyDatabase(Database *);

// Search database for a dragon by name or ID
// Returns its array index or -1 if not found
int searchForDragon(const Database *const, const char *);

// Gather min and max values for fierceness, #volant and #non-volant
void getDatabaseInfo(const Database *const, size_t *const, size_t *const, size_t *const, size_t *const);

// Finds the array index given a dragon's id
// Returns -1 if not found
int idToIndex(const Database *const, const unsigned int *const);

// Delete a dragon by array index
// If not last, copies dragon at index + 1
// Returns true if dragon was last in array
bool deleteDragon(Database *const, const unsigned int *const);

// Sort the database in ascending order, bool = true by name, bool = false by id
void sortDragons(Database *const, const bool);

#endif