#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include "database.h"

// Prompts user for the filename of the database (e.g. "dragons.txt")
void getDatabaseFilename(char *const str);

// Prints the initial welcome message.
void printWelcomeMessage();

// Prints the menu.
void printMenu();

// Contains functionality of the menu
void executeCommands(Database *const db);

#endif