#include "userinterface.h"
#include "filehandler.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
 
void printWelcomeMessage(void) {
    printf("\nThis program helps organize information about dragons. You may add and\n");
    printf("remove dragons and their attributes, list the dragons currently in the\n");
    printf("database, and their attributes, look up the attributes of an individual\n");
    printf("dragon, get statistics from the database, or sort the database.\n");
}
 
void printMenu(void){
    puts("---------------------------------------------------------------");
    puts("Menu");
    puts("---------------------------------------------------------------");
    puts("0. Display menu.");
    puts("1. Insert a dragon.");
    puts("2. Update a dragon.");
    puts("3. Delete a dragon.");
    puts("4. List all dragons (brief).");
    puts("5. List all dragons (detailed).");
    puts("6. Show details for a specific dragon.");
    puts("7. List database statistics.");
    puts("8. Sort database.");
    puts("-1. Quit.");
    puts("---------------------------------------------------------------");
}
 
void executeCommands(Database *db)
{
    int choice = -2;
    while (choice != -1)
    {
        printf("\n?: ");
        fflush(stdin);
        scanf("%2d", &choice); // never goes to default by this read
 
        switch (choice)
        {
        case 0:
            printMenu();
            break;
        case 1:
 
            break;
        case 2:
            updateOneDragon(db);
            break;
        case 3:
 
            break;
        case 4:
            listAllDragonsBrief(db);
            break;
        case 5:
            listAllDragonsDetailed(db);
            break;
        case 6:
            listOneDragonDetailed(db);
            break;
        case 7:
            listDatabaseStatistics(db);
            break;
        case 8:
 
            break;
        case -1:
            printf("\nHave a good one! See ya!\n");
            choice = -1;
            break;
        default:
            puts("\nInvalid selection. Please try again.");
            break;
        }
    }
}
 
static void listAllDragonsBrief(const Database *db) {
    // print each dragons name and id (from the database)
    printf("---------------------------------------------------------------\n");
    printf("ID Name\n");
    printf("---------------------------------------------------------------\n");
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        printf(" %u %s\n",(*db).dragons[drgIdx].id, (*db).dragons[drgIdx].name);
    }
}
 
static void listAllDragonsDetailed(const Database *db) {
    // print each dragons name and id (from the database)
    printf("---------------------------------------------------------------\n");
    printf("ID Name\t\tVolant Fierceness #Colours Colors\n");
    printf("---------------------------------------------------------------\n");
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        printf(" %1u %s", (*db).dragons[drgIdx].id, (*db).dragons[drgIdx].name);
        printf("\t%6c %10u %8u", (*db).dragons[drgIdx].isVolant, (*db).dragons[drgIdx].fierceness, (*db).dragons[drgIdx].numColours); 
        for (size_t clrIdx = 0; clrIdx < (*db).dragons[drgIdx].numColours; clrIdx++) {
            printf(" %s", (*db).dragons[drgIdx].colours[clrIdx]);
        }
        puts("");
    }
}
 
static bool getIsValidID(char str[], bool isStrValidId){
    /* Ensure that input is a number */
    for( size_t drgIdx = 0; ; drgIdx++){

        if(str[drgIdx] == 0) {
            isStrValidId = true;
            break;
        }

        if(!isdigit(str[drgIdx])){ 
            isStrValidId = false;
            break;
        }
    }
    return isStrValidId;
}

static bool getIsValidNAME(char str[], bool isStrValidName) {
        /* Ensure that input is a valid char (drgIdx.e. a-zA-Z) using ASCII table*/
        for (size_t i = 0; ; i++) {

            if(str[i] == 0) {
                isStrValidName = true;
                break;
            }
            
            if(str[i] <= 65 && str[i] >= 90 || str[i] <= 97 && str[i] >= 122) {
                isStrValidName = false;
                break;
            }
        }
    return isStrValidName;
}

bool getIfIdInDB(const Database *db, const bool isStrValidId, const char str[], bool isIdInDB) {
    // check if the string ID exists in the database
    if(isStrValidId == true) { // putting equals true for readablility
        unsigned int nR = strtoul(str, NULL, 10);
        if( nR <= (*db).size ) {
            isIdInDB = true;
        } else {
            isIdInDB = false;
        }
    }
    return isIdInDB;   
}

bool getIfNameInDB(const Database *db, const bool isStrValidName, const char str[], bool isNameInDB) {
    // check if the string NAME exists in database
    if(isStrValidName == true) { // putting equals true for readablility
        for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
            for (size_t charIdx = 0; ; charIdx++) {

                if(str[charIdx] == 0) {
                    isNameInDB = true;
                    break;
                }

                if ((*db).dragons[drgIdx].name[charIdx] != str[charIdx])
                {
                    break;
                }
            }
            if(isNameInDB == true) {
                break;
            }
        }
    } else {
        isNameInDB = false;
    } 
    return isNameInDB;
}

static unsigned short findDragonIndex(char str[], bool isIdInDB, bool isNameInDB, const Database *db) {
    unsigned short idx = strtoul(str, NULL, 10) - 1;
    if (isIdInDB == true) {
        return idx;
    } // end id if
    else if(isNameInDB == true) {
        for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) { // grab each dragon sequentially
            for (size_t charIdx = 0; ; charIdx++) { // grab the first character within its name and check if it equals all chars of the input array

                if (str[charIdx] == 0) {
                    return drgIdx;
                } // end if

                if (str[charIdx] != (*db).dragons[drgIdx].name[charIdx])
                {
                    break;
                }
            } // end inner loop
        } // end outer loop
    } // end name if
    else {
        printf("--> Err: No dragon with input Id or Name exists in the Database\n");
    }
}

static void printSpecificDragon(const Database *db, unsigned short drgIdx) {
    printf("\n---------------------------------------------------------------\n");
    printf("ID Name\t\tVolant Fierceness #Colours Colors\n");
    printf("---------------------------------------------------------------\n");
    printf(" %1u %s", (*db).dragons[drgIdx].id, (*db).dragons[drgIdx].name);
    printf("\t%6c %10u %8u", (*db).dragons[drgIdx].isVolant, (*db).dragons[drgIdx].fierceness, (*db).dragons[drgIdx].numColours); 
    for (size_t clrIdx = 0; clrIdx < (*db).dragons[drgIdx].numColours; clrIdx++) {
        printf(" %s", (*db).dragons[drgIdx].colours[clrIdx]);
    }
    puts("");
}

static void toUpper(char* string) {
    const char OFFSET = 'a' - 'A';
    while (*string)
    {
        *string = (*string >= 'a' && *string <= 'z') ? *string -= OFFSET : *string;
        string++;
    }
}

static void getDragonIdOrName(char *const str) {
    printf("Enter id or name of dragon: ");
    fflush(stdin);
    scanf("%24s", str);
}

static void listOneDragonDetailed(const Database *db) {
    // reads input
    char str[MAX_NAME] = {0};
    puts("");
    getDragonIdOrName(str);

    // check if input is a number or string a-zA-Z
    bool isStrValidId, isStrValidName, isIdInDB = 0, isNameInDB = 0; // meaning: is str valid dragon id or name
    unsigned short drgIdx; // variable to store index for the dragon we found
    isStrValidId = getIsValidID(str, isStrValidId); // check if input is an int
    isStrValidName = getIsValidNAME(str, isStrValidName); // check if input is wholly a part of english alphabet, drgIdx.e. a-zA-Z

    // if we have a str with alphabet chars, then make them all into uppercase
    if (isStrValidName) // excludes isStrValidID
    {
        toUpper(str);
    }

    // check if input even exists in the database
    isIdInDB = getIfIdInDB(db, isStrValidId, str, isIdInDB);
    isNameInDB = getIfNameInDB(db, isStrValidName, str, isNameInDB);
    

    // find the index of the dragon that we know exists in the database
    drgIdx = findDragonIndex(str, isIdInDB, isNameInDB, db);
    
    //print the dragon with index drgIdx
    if (isIdInDB || isNameInDB)
    {
        printSpecificDragon(db, drgIdx);
    }
}

static void getMinFierceness(const Database *db, unsigned int* minFierceness){
    *minFierceness = 10; // highest possible fierceness
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        if (*minFierceness > (*db).dragons[drgIdx].fierceness)
        {
            *minFierceness = (*db).dragons[drgIdx].fierceness;
        }
    }
}

static void getMaxFierceness(const Database *db, unsigned int* maxFierceness){
    *maxFierceness = 1; // smallest possible fierceness
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        if (*maxFierceness < (*db).dragons[drgIdx].fierceness)
        {
            *maxFierceness = (*db).dragons[drgIdx].fierceness;
        }
    }
}

static void getVolantCount(const Database *db, unsigned int* volant) {
    *volant = 0;
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        if ((*db).dragons[drgIdx].isVolant == (int)'Y')
        {
            (*volant)++;
        }
        
    }
}

static void getWithoutVolantCount(const Database *db,  unsigned int* withoutVolant) {
    *withoutVolant = 0;
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        if ((*db).dragons[drgIdx].isVolant == (int)'N')
        {
            (*withoutVolant)++; 
        }
        // if we always will get volant filled it suffices to only get volant,
        // then takes size-volant = withoutVolant, but if we have missing values 
        // that won't cutt the deal, for safe-coding I prefer this. 
    }
}

static void listDatabaseStatistics(const Database *db){
    printf("\n---------------------------------------------------------------\n");
    printf("Size MinFierceness MaxFierceness #Volant #Nonvolant\n");
    printf("---------------------------------------------------------------\n");
    unsigned int minFierceness, maxFierceness, volant, withoutVolant;
    getMinFierceness(db, &minFierceness);
    getMaxFierceness(db, &maxFierceness);
    getVolantCount(db, &volant);
    getWithoutVolantCount(db, &withoutVolant);
    printf("%4u %13u %13u %7u %11u\n", (*db).size, minFierceness, maxFierceness, volant, withoutVolant);
}

static bool changeDragonVolant(char *volant){
    bool isValidVolant = false;
    char newVolant;
    printf("Enter volant (Y, N): ");
    fflush(stdin);
    newVolant = fgetchar();
    if (newVolant == 'y' || newVolant == 'Y') {
        *volant = 'Y';
        isValidVolant = true;
    } else if (newVolant == 'n' || newVolant == 'N') {
        *volant = 'N';
        isValidVolant = true;
    }    
    return isValidVolant;
}

static bool changeDragonFierceness(unsigned int *fierceness) {
    bool isValidFierceness = false;
    char fierceArr[3]; // only three slots, 2 for numbers (10 has two slots) and the null sign
    printf("Enter fierceness (1-10): ");
    fflush(stdin);
    scanf("%2s", fierceArr);
    unsigned short nr = strtoul(fierceArr, NULL, 10); // returns 0 if unsuccessful
    if(nr >= 1 && nr <= 10) {
        *fierceness = nr;
        isValidFierceness = true;
    }
    return isValidFierceness;
}

static void changeDragonColours(Dragon *dragon) {
    bool continueGetting = true;
    // get all the colours
    for (int currCol = 0; currCol < MAX_COLOURS; currCol++)
    {
        if (continueGetting == true)
        {
            char* colour = calloc(MAX_COLOUR_NAME, sizeof(char));
            printf("Colour %d (of %d): ", (currCol+1), MAX_COLOURS);
            fflush(stdin);
            fgets(colour, 24, stdin); // reads including and until the newline character
            if(*colour == '\n') {
                dragon->numColours = currCol;
                continueGetting = false;
            }
            int i = 0;
            while (colour[i] != '\n') {
                if(!isalpha(colour[i])) { // checks ascii: a-zA-Z
                    printf("-->Err: Failed to allocate colour. Invalid colour name\n");
                    dragon->numColours = currCol;
                    continueGetting = false;
                    break;
                }
                i++;
            }
            if(colour[i] == '\n') { // removes the newline character, not necessary anymore
                colour[i] = 0;
            }
            toUpper(colour);
            free(dragon->colours[currCol]);
            dragon->colours[currCol] = colour;
        } 
        if (continueGetting == false)
        {
            free(dragon->colours[currCol]);
            dragon->colours[currCol] = NULL;
        }
    }
}

void updateOneDragon(Database *db) {
    char str[MAX_NAME] = {0};
    getDragonIdOrName(str);

    // check if valid format on input
    bool isStrValidId, isStrValidName, isIdInDB = 0, isNameInDB = 0; // meaning: is str valid dragon id or name
    isStrValidId   = getIsValidID(str, isStrValidId); // check if input is an int
    isStrValidName = getIsValidNAME(str, isStrValidName); // check if input is wholly a part of english alphabet, drgIdx.e. a-zA-Z

    if (isStrValidName) // excludes isStrValidID
    {
        toUpper(str);
    }

    if(isStrValidId || isStrValidName) {
        // if we have a str with alphabet chars, then make them all into uppercase

        // check if input is in database
        isIdInDB       = getIfIdInDB(db, isStrValidId, str, isIdInDB);
        isNameInDB     = getIfNameInDB(db, isStrValidName, str, isNameInDB);

        if(isIdInDB || isNameInDB) {
            // find the index of the dragon that we know exists in the database
            unsigned short drgIdx; // variable to store index for the dragon we found
            drgIdx = findDragonIndex(str, isIdInDB, isNameInDB, db);

            // update dragon with "str" name or id found within database with new values on volant, fierceness and colours
            // first update the volant
            bool isValidVolant = changeDragonVolant(&(*db).dragons[drgIdx].isVolant);
            if (isValidVolant == true)
            {
                bool isValidFierceness = changeDragonFierceness(&(*db).dragons[drgIdx].fierceness);
                if (isValidFierceness == true)
                {
                    changeDragonColours(&(*db).dragons[drgIdx]);
                    saveDatabase("mahmut/files/Dragons.txt", db);
                    loadDatabase("mahmut/files/Dragons.txt", db);
                    puts("Dragon updated."); 
                } else {
                    printf("--->Err: Given fierceness is out of bound (1-10)\n");
                }
                
            } else {
                printf("--->Err: Given Volant is invalid (Y, N)\n");
            }
                
        } else {
            printf("--->Err: Given ID or NAME is not in the database\n");
        }
    }
}