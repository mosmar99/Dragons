#include "userinterface.h"
#include "database.h"
 
void printWelcomeMessage(void) {
    printf("This program helps organize information about dragons. You may add and\n");
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
    puts("2. Update a drago.");
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
        scanf("%2d[-012345678]", &choice);
 
        switch (choice)
        {
        case 0:
            printMenu();
            break;
        case 1:
 
            break;
        case 2:
 
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
            puts("\nInvalid selection. Please try again.\n");
            break;
        }
    }
}
 
void listAllDragonsBrief(const Database *db) {
    // print each dragons name and id (from the database)
    printf("---------------------------------------------------------------\n");
    printf("ID Name\n");
    printf("---------------------------------------------------------------\n");
    for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
        printf(" %u %s\n",(*db).dragons[drgIdx].id, (*db).dragons[drgIdx].name);
    }
}
 
void listAllDragonsDetailed(const Database *db) {
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

static bool getIsValidNAME(bool isStrValidId, char str[], bool isStrValidName) {
    if(isStrValidId == false) {
        /* Ensure that input is a valid char (drgIdx.e. a-zA-Z) using ASCII table*/

        for (size_t drgIdx = 0; ; drgIdx++) {

            if(str[drgIdx] == 0) {
                isStrValidName = true;
                break;
            }
            
            if(str[drgIdx] <= 65 && str[drgIdx] >= 90 || str[drgIdx] <= 97 && str[drgIdx] >= 122) {
                isStrValidName = false;
                break;
            }
        }
    } 
    return isStrValidName;
}

static bool getIfIdInDB(const bool isStrValidId, bool isIdInDB, const char str[], const Database *db) {
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

static bool getIfNameInDB(bool isStrValidName, const Database *db, char str[], bool isNameInDB){
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

static void printSpecificDragon(char str[], bool isIdInDB, bool isNameInDB, const Database *db) {
    unsigned int id = strtoul(str, NULL, 10)-1;
    bool foundDragonName = false;
    if (isIdInDB == true) {
        printf("\n---------------------------------------------------------------\n");
        printf("ID Name\t\tVolant Fierceness #Colours Colors\n");
        printf("---------------------------------------------------------------\n");
        printf(" %1u %s", (*db).dragons[id].id, (*db).dragons[id].name);
        printf("\t%6c %10u %8u", (*db).dragons[id].isVolant, (*db).dragons[id].fierceness, (*db).dragons[id].numColours); 
        for (size_t clrIdx = 0; clrIdx < (*db).dragons[id].numColours; clrIdx++) {
            printf(" %s", (*db).dragons[id].colours[clrIdx]);
        } // end loop
        puts("");
    } // end if
    else if(isNameInDB == true) {
        for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) { // grab each dragon sequentially
            for (size_t charIdx = 0; ; charIdx++) { // grab the first character within its name and check if it equals all chars of the input array

                if (str[charIdx] == 0) {
                    printf("\n---------------------------------------------------------------\n");
                    printf("ID Name\t\tVolant Fierceness #Colours Colors\n");
                    printf("---------------------------------------------------------------\n");
                    printf(" %1u %s", (*db).dragons[drgIdx].id, (*db).dragons[drgIdx].name);
                    printf("\t%6c %10u %8u", (*db).dragons[drgIdx].isVolant, (*db).dragons[drgIdx].fierceness, (*db).dragons[drgIdx].numColours); 
                    for (size_t clrIdx = 0; clrIdx < (*db).dragons[drgIdx].numColours; clrIdx++) {
                        printf(" %s", (*db).dragons[drgIdx].colours[clrIdx]);
                    }
                    break;
                } // end if

                if(str[charIdx] != (*db).dragons[drgIdx].name[charIdx]){
                    break;
                } // end if
            } // end inner loop
        } // end outer loop
        puts("");
    } // end if
    else {
        printf("--> Err: No dragon with input Id or Name exists in the Database\n");
    }
}

void listOneDragonDetailed(const Database *db) {
    // reads input
    char str[MAX_NAME] = {0};
    bool isStrValidId, isStrValidName; // meaning: is str valid dragon id or name
    bool isIdInDB = 0, isNameInDB = 0;
    printf("\nEnter id or name of dragon: ");
    fflush(stdin);
    scanf("%49s", str);

    isStrValidId = getIsValidID(str, isStrValidId); // check if input is an int
    isStrValidName = getIsValidNAME(isStrValidId, str, isStrValidName); // check if input is wholly a part of english alphabet, drgIdx.e. a-zA-Z
    isIdInDB = getIfIdInDB(isStrValidId, isIdInDB, str, db);
    isNameInDB = getIfNameInDB(isStrValidName, db, str, isNameInDB);
    printSpecificDragon(str, isIdInDB, isNameInDB, db);
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

void listDatabaseStatistics(const Database *db){
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