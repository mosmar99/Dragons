#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <stdio.h>
#include "database.h"

// Prints the initial welcome message.
void printWelcomeMessage();

// Prints the menu.
void printMenu();

// Contains functionality of the menu
void executeCommands(Database *);

// Prints a list of all dragons (brief)
void listAllDragonsBrief(const Database *const);

// Prints a list of all dragons (detailed)
void listAllDragonsDetailed(const Database *const);

// Prints one dragon
void printOneDragon(const Database *const);

// Get an ID or name of dragon from user
void getDragonNameOrId(char *);

// Prints statistics of the database
void printDatabaseInfo(const Database *const);

#endif