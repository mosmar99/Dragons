#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <stdio.h>
#include "database.h"
#include "filehandler.h"

// Prints the initial welcome message.
void printWelcomeMessage();

// Prints the menu.
void printMenu();

// Contains functionality of the menu
void executeCommands(Database *const);

// Prompts user for the filename of the database (e.g. "dragons.txt")
void getDatabaseFilename(char *);

// Prints a list of all dragons (brief)
void listAllDragonsBrief(const Database *const);

// Prints a list of all dragons (detailed)
void listAllDragonsDetailed(const Database *const);

// Get an ID or name of dragon from user
void getDragonNameOrId(char *const);

// Prints one dragon
void printOneDragon(const Database *const);

// Prints statistics of the database
void printDatabaseInfo(const Database *const);

// Handles updating a dragon
void doUpdateDragon(Database *const);

// Handles inserting a new dragon
void doInsertDragon(Database *const);

// Handles deleting a dragon
void doDeleteDragon(Database *const);

// Handles sorting the database
void doSortDragons(Database *const);

#endif