#include "userinterface.h"

void printWelcomeMessage() {
    printf("This program helps organize information about dragons. You may add and\n");
    printf("remove dragons and their attributes, list the dragons currently in the\n");
    printf("database, and their attributes, look up the attributes of an individual\n");
    printf("dragon, get statistics from the database, or sort the database.\n");
}

void getMenu(void){
    puts("------------------------------------------");
    puts("Menu");
    puts("------------------------------------------");
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
    puts("------------------------------------------");
}

void executeCommands()
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
            getMenu();
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

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