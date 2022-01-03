#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include "database.h"

// Error strings used in error messages
#define ERROR_STRING_MENU_SELECTION "\nInvalid selection. Please try again.\n"
#define ERROR_STRING_NAME_VALID "Error: only letters in the english alphabet is allowed\n"
#define ERROR_STRING_COLOUR_VALID ERROR_STRING_NAME_VALID

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