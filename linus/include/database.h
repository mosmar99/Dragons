#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

// Prompts user for the filename of the database (e.g. "dragons.txt")
void getDatabaseFilename(char *);

// Frees the RAM memory occupied by a Database
void destroyDatabase(Database *);

// Search database for a dragon by name or ID
// Returns its index or -1 if not found
int searchForDragon(const Database *const, const char *);

// Returns whether or not the string entered by user is an integer or name 
bool isID(const char *const);

// Gather min and max values for fierceness and #volant and #non-volant
void getDatabaseInfo(const Database *const, size_t *const, size_t *const, size_t *const, size_t *const);

#endif