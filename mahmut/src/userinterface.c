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
 
void listOneDragonDetailed(const Database *db) {
    // reads input
    char str[MAX_NAME] = {0};
    bool isStrValidId, isStrValidName; // meaning: is str valid dragon id or name
    bool isIdInDB = 0, isNameInDB = 0;
    printf("\nEnter id or name of dragon: ");
    fflush(stdin);
    scanf("%49s", str);

    /* Ensure that input is a number */
    for( size_t i = 0; ; i++){

        if(str[i] == 0) {
            isStrValidId = true;
            break;
        }

        if(!isdigit(str[i])){ 
            isStrValidId = false;
            break;
        }
    }

    if(isStrValidId == false) {
        /* Ensure that input is a valid char (i.e. a-zA-Z) using ASCII table*/

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

    } 

    // check if the string ID exists in the database
    if(isStrValidId == true) { // putting equals true for readablility
        unsigned int nR = strtoul(str, NULL, 10);
        if( nR <= (*db).size ) {
            isIdInDB = true;
        } else {
            isIdInDB = false;
        }
    }

    // check if the string NAME exists in database
    if(isStrValidName == true) { // putting equals true for readablility
        for (size_t drgIdx = 0; drgIdx < (*db).size; drgIdx++) {
            for (size_t i = 0; ; i++) {

                if(str[i] == 0) {
                    isNameInDB = true;
                    break;
                }

                if ((*db).dragons[drgIdx].name[i] != str[i])
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

}