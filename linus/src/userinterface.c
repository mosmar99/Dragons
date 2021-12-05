#include "userinterface.h"

void printWelcomeMessage()
{
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
            printWelcomeMessage();
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
            choice = -1;
            break;
        default:
            puts("\nPlease enter a valid option\n");
            break;
        }
    }
}