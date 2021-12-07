#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <stdio.h>

// Prints welcome message
void printWelcomeMessage(void);

// Contains functionality of the menu
void executeCommands(Database *database);

// prints the menu
void printMenu(void);

#endif