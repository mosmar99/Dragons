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

#endif