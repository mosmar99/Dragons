#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

/*
File: userinterface.h
Description: 
This file contains the interface of printing to the screen and handling the inputs from the user
*/

#include "database.h"

// Prompts user for the filename of the database (e.g. "dragons.txt")
// Parameter: (the string to be the relative path to the .txt file)
void getDatabaseFilename(char *const str);

// Prints the initial welcome message.
void printWelcomeMessage();

// Prints the menu.
void printMenu();

// Contains functionality of the menu
// Parameters: (a database)
void executeCommands(Database *const db);

#endif