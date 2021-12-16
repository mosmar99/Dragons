#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
 
#include "database.h"
 
// Prints welcome message
void printWelcomeMessage(void);
 
// prints the menu
void printMenu(void);
 
// Contains functionality of the menu
void executeCommands(Database *database);
 
// display brief (i.e: Name and ID) information about all dragons within the database
static void listAllDragonsBrief(const Database *db);
 
// display detailed information about all dragons within the database
// ID, Name, Volant, #Colours, Colors
static void listAllDragonsDetailed(const Database *db);
 
// display detailed information about ONE dragon within the database based on Name or Id
// ID, Name, Volant, #Colours, Colors
static void listOneDragonDetailed(const Database *db);

// display detailed information about ONE dragon within the database based on Name or Id
// ID, Name, Volant, #Colours, Colors
static void listOneDragonDetailed(const Database *db);

static bool getIsValidID(char str[], bool isStrValidId);

static bool getIsValidNAME(char str[], bool isStrValidName);

bool getIfIdInDB(const Database *db, const bool isStrValidId, const char str[], bool isIdInDB);

bool getIfNameInDB(const Database *db, const bool isStrValidName, const char str[], bool isNameInDB);

static void printSpecificDragon(const Database *db, unsigned short drgIdx);

static unsigned short findDragonIndex(char str[], bool isIdInDB, bool isNameInDB, const Database *db);

static void getDragonIdOrName(char *const str);

static void toUpper(char* string);

static void listDatabaseStatistics(const Database *db);

static void getMinFierceness(const Database *db, unsigned int* minFierceness);

static void getMaxFierceness(const Database *db, unsigned int* maxFierceness);

void updateOneDragon(Database *db);

static bool changeDragonVolant(char *volant);

static bool changeDragonFierceness(unsigned int *fierceness);

static void changeDragonColours(Dragon *dragon);

#endif
