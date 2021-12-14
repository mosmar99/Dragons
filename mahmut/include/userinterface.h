#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
 
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "stdbool.h"
#include "database.h"
 
// Prints welcome message
void printWelcomeMessage(void);
 
// prints the menu
void printMenu(void);
 
// Contains functionality of the menu
void executeCommands(Database *database);
 
// display brief (i.e: Name and ID) information about all dragons within the database
void listAllDragonsBrief(const Database *db);
 
// display detailed information about all dragons within the database
// ID, Name, Volant, #Colours, Colors
void listAllDragonsDetailed(const Database *db);
 
// display detailed information about ONE dragon within the database based on Name or Id
// ID, Name, Volant, #Colours, Colors
void listOneDragonDetailed(const Database *db);
 
#endif

