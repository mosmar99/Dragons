#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <stdio.h>
#include "database.h"

// Prints welcome message
void printWelcomeMessage(void);

// prints the menu
void printMenu(void);

// Contains functionality of the menu
void executeCommands(Database *database);

#endif