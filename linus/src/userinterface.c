#include "userinterface.h"

void printWelcomeMessage()
{
    puts("This program helps organize information about dragons. You may add and");
    puts("remove dragons and their attributes, list the dragons currently in the");
    puts("database, and their attributes, look up the attributes of an individual");
    puts("dragon, get statistics from the database, or sort the database.");
}

void printMenu()
{
    puts("------------------------------------------");
    puts("Menu");
    puts("------------------------------------------");
    puts(" 0. Display menu.");
    puts(" 1. Insert a dragon.");
    puts(" 2. Update a dragon.");
    puts(" 3. Delete a dragon.");
    puts(" 4. List all dragons (brief).");
    puts(" 5. List all dragons (detailed).");
    puts(" 6. Show details for a specific dragon.");
    puts(" 7. List database statistics.");
    puts(" 8. Sort database.");
    puts("-1. Quit.");
    puts("------------------------------------------");
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
            printOneDragon(db);
            break;
        case 7:
            printDatabaseInfo(db);
            break;
        case 8:

            break;
        case -1:
            choice = -1;
            puts("Have a good one! See ya!");
            break;
        default:
            puts("\nInvalid selection. Please try again.");
            break;
        }
    }
}

void listAllDragonsBrief(const Database *const db)
{
    puts("");
    const size_t idWidth = 4;
    puts("--------------------------------------------------------------------------------");
    printf("%*s  %s\n", idWidth, "ID", "Name");
    puts("--------------------------------------------------------------------------------");

    // loop through all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // print id
        printf("%*llu  ", idWidth, db->dragons[dragonIndex].id);

        // print name
        printf("%s\n", db->dragons[dragonIndex].name);
    }
}

void listAllDragonsDetailed(const Database *const db)
{
    puts("");
    const size_t idWidth = 5;
    const size_t nameWidth = MAX_NAME;
    const size_t volantWidth = 6;
    const size_t fiercenessWidth = 10;
    const size_t numColoursWidth = 8;
    const size_t coloursWidth = MAX_COLOURS * MAX_COLOUR_NAME;
    puts("--------------------------------------------------------------------------------");
    printf("%*s  %-*s%s  %*s  %*s  %-*s\n", idWidth, "ID", nameWidth, "Name", "Volant", fiercenessWidth, "Fierceness", numColoursWidth, "#Colours", coloursWidth, "Colours");
    puts("--------------------------------------------------------------------------------");

    // loop through all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // print id
        printf("%*llu", idWidth, db->dragons[dragonIndex].id);

        // print name
        printf("  %-*s", nameWidth, db->dragons[dragonIndex].name);

        // print volant
        printf("%*c", volantWidth, db->dragons[dragonIndex].isVolant);

        // print fierceness
        printf("  %*llu", fiercenessWidth, db->dragons[dragonIndex].fierceness);

        // print # of colours
        printf("  %*llu  ", numColoursWidth, db->dragons[dragonIndex].numColours);

        // print all colours
        for (size_t i = 0; i < db->dragons[dragonIndex].numColours; i++)
        {
            printf("%s ", db->dragons[dragonIndex].colours[i]);
        }

        puts("");
    }
}

void printOneDragon(const Database *const db)
{
    puts("");
    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int id = searchForDragon(db, identifier);
    if (id < 1 || id > db->size)
    {
        puts("Error: dragon not found");
        return;
    }
    id--; // dragon id start at 1, not 0
    const size_t idWidth = 5;
    const size_t nameWidth = MAX_NAME;
    const size_t volantWidth = 6;
    const size_t fiercenessWidth = 10;
    const size_t numColoursWidth = 8;
    const size_t coloursWidth = MAX_COLOURS * MAX_COLOUR_NAME;
    puts("--------------------------------------------------------------------------------");
    printf("%*s  %-*s%s  %*s  %*s  %-*s\n", idWidth, "ID", nameWidth, "Name", "Volant", fiercenessWidth, "Fierceness", numColoursWidth, "#Colours", coloursWidth, "Colours");
    puts("--------------------------------------------------------------------------------");

    // print id
    printf("%*llu", idWidth, db->dragons[id].id);

    // print name
    printf("  %-*s", nameWidth, db->dragons[id].name);

    // print volant
    printf("%*c", volantWidth, db->dragons[id].isVolant);

    // print fierceness
    printf("  %*llu", fiercenessWidth, db->dragons[id].fierceness);

    // print # of colours
    printf("  %*llu  ", numColoursWidth, db->dragons[id].numColours);

    // print all colours
    for (size_t i = 0; i < db->dragons[id].numColours; i++)
    {
        printf("%s ", db->dragons[id].colours[i]);
    }

    puts("");
}

void getDragonNameOrId(char *identifier)
{
    printf("\nEnter ID or name of dragon: ");
    scanf("%24s", identifier);
}

void printDatabaseInfo(const Database *const db)
{
    puts("");
    const size_t sizeWidth = 4;
    const size_t fiercenessWidth = 13;
    const size_t volantWidth = 7;
    const size_t nonVolantWidth = 10;

    size_t max;
    size_t min;
    size_t volant;
    size_t nonVolant;
    getDatabaseInfo(db, &max, &min, &volant, &nonVolant);

    puts("---------------------------------------------------------");
    printf("%*s  %*s  %*s  %*s  %*s\n", sizeWidth, "Size", fiercenessWidth, "MinFierceness", fiercenessWidth, "MaxFierceness", volantWidth, "#Volant", nonVolantWidth, "#NonVolant");
    puts("---------------------------------------------------------");

    // print size
    printf("%*llu", sizeWidth, db->size);

    // don't print anything else if database is empty
    if (db->size > 0)
    {
        // print min fierceness
        printf("  %*llu", fiercenessWidth, min);

        // print max fierceness
        printf("  %*llu", fiercenessWidth, max);

        // print volant
        printf("  %*llu", volantWidth, volant);

        // print non-volant
        printf("  %*llu", nonVolantWidth, nonVolant);

        puts("");
    }
}
