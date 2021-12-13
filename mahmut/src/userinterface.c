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

