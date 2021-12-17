#include "userinterface.h"
#include "filehandler.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Prints a list of all dragons (brief)
static void listAllDragonsBrief(const Database *const db);

// Prints a list of all dragons (detailed)
static void listAllDragonsDetailed(const Database *const db);

// Get an ID or name of dragon from user
static void getDragonNameOrId(char *const str);

// Prints one dragon
static void printOneDragon(const Database *const db);

// Prints statistics of the database
static void printDatabaseInfo(const Database *const db);

// Handles updating a dragon
static void doUpdateDragon(Database *const db);

// Handles inserting a new dragon
static void doInsertDragon(Database *const db);

// Handles deleting a dragon
static void doDeleteDragon(Database *const db);

// Handles sorting the database
static void doSortDragons(Database *const db);

// Update a dragon's attributes, excl. name and id
static void updateDragon(Dragon *const db);

// Converts a string to all uppercase
static void stringToUppercase(char *const str);

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

void executeCommands(Database *const db)
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
            doInsertDragon(db);
            break;
        case 2:
            doUpdateDragon(db);
            break;
        case 3:
            doDeleteDragon(db);
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
            doSortDragons(db);
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

void getDatabaseFilename(char *const filename)
{
    printf("Enter the name of the database: ");
    fflush(stdin);
    scanf("%49s", filename);
}

void listAllDragonsBrief(const Database *const db)
{
    puts("");
    const size_t idWidth = 5;
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
            printf("%s ", *(db->dragons[dragonIndex].colours + i));
        }

        puts("");
    }
}

void getDragonNameOrId(char *const identifier)
{
    printf("\nEnter ID or name of dragon: ");
    fflush(stdin);
    scanf("%24s", identifier);
    stringToUppercase(identifier);
}

void printOneDragon(const Database *const db)
{
    puts("");
    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int ix = searchForDragon(db, identifier);
    if (ix < 0 || ix >= db->size)
    {
        return;
    }
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
    printf("%*llu", idWidth, db->dragons[ix].id);

    // print name
    printf("  %-*s", nameWidth, db->dragons[ix].name);

    // print volant
    printf("%*c", volantWidth, db->dragons[ix].isVolant);

    // print fierceness
    printf("  %*llu", fiercenessWidth, db->dragons[ix].fierceness);

    // print # of colours
    printf("  %*llu  ", numColoursWidth, db->dragons[ix].numColours);

    // print all colours
    for (size_t i = 0; i < db->dragons[ix].numColours; i++)
    {
        printf("%s ", *(db->dragons[ix].colours + i));
    }

    puts("");
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

void doUpdateDragon(Database *const db)
{
    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int ix = searchForDragon(db, identifier);
    if (ix < 0)
    {
        return;
    }
    puts("");
    updateDragon(&db->dragons[ix]);
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon updated.");
}

void doInsertDragon(Database *const db)
{
    // check if it's needed to expand database capacity
    if (db->size == db->capacity)
    {
        expandCapacity(db);
        saveDatabase(NULL, db);
        loadDatabase(NULL, db);
    }

    db->dragons[db->size] = *(Dragon *)calloc(sizeof(Dragon), sizeof(char));
    if (!&db->dragons[db->size])
    {
        fprintf(stderr,"Error: failed to allocate memory for new dragon\n");
        getchar();
        exit(-1);
    }

    // id
    db->dragons[db->size].id = db->nextId++;
    const int ix = idToIndex(db, &db->dragons[db->size++].id);
    assert(ix > 0);

    // name
    db->dragons[ix].name = calloc(MAX_NAME, sizeof(char));
    if (!db->dragons[ix].name)
    {
        
        fprintf(stderr,"Error: failed to allocate memory for new dragon's name\n");
        getchar();
        exit(-1);
    }
    char name[MAX_NAME - 1];
    printf("\nEnter name: ");
    scanf("%24s", name);
    stringToUppercase(name);
    strcpy(db->dragons[ix].name, name);

    // rest of the attributes
    updateDragon(&db->dragons[ix]);
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon inserterd.");
}

void doDeleteDragon(Database *const db)
{
    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int ix = searchForDragon(db, identifier);
    if (ix < 0)
    {
        return;
    }
    // Delete the dragon by repeatedly copying dragons 1 step left and lastly freeing
    // memory of the last dragon (which has by then copied 1 step left in array)
    while (!deleteDragon(db, &ix))
    {
        ix++;
    }
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon deleted.");
}

void doSortDragons(Database *const db)
{
    if (db->size <= 1)
    {
        return; // pointless to sort empty array or array of size 1
    }

    puts("");
    unsigned short choice = 2;
    do
    {
        printf("Enter sort by ID (0) or Name (1): ");
        fflush(stdin);
        scanf("%1hu[01]", &choice);
    } while (!(choice == 0 || choice == 1));

    sortDragons(db, (bool)choice);
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Database sorted.");
}

void updateDragon(Dragon *const dragon)
{
    // update volant
    char volantTest;
    printf("Enter volant (Y, N): ");
    fflush(stdin);
    scanf("%c", &volantTest);
    volantTest = toupper(volantTest);
    if (volantTest != 'Y' && volantTest != 'N')
    {
        fprintf(stderr,"Error: invalid volant input");
        fprintf(stderr,"Default: N\n");
        dragon->isVolant = 'N';
    }
    else
    {
        dragon->isVolant = volantTest;
    }

    // update fierceness
    int fierceTest;
    printf("Enter fierceness (1-10): ");
    fflush(stdin);
    scanf("%2d[0123456789]", &fierceTest);
    if (fierceTest < 1 || fierceTest > 10)
    {
        fprintf(stderr,"Error: invalid range\n");
        fprintf(stderr,"Default: 1\n");
        dragon->fierceness = 1;
    }
    else
    {
        dragon->fierceness = fierceTest;
    }

    // update all colours
    size_t newColours = 0;
    size_t originalColours = dragon->numColours;
    for (size_t i = 0; i < MAX_COLOURS; i++)
    {
        char colour[MAX_COLOUR_NAME - 1];
        printf("Colour (%llu of %llu) (0 to stop): ", i + 1, MAX_COLOURS);
        fflush(stdin);
        scanf("%24s", colour);
        for (char *ix = colour; *ix != '\0'; ix++)
        {
            *ix = toupper(*ix);
        }

        if (*colour == '0')
        {
            // free the remaining colours
            for (size_t j = i; j < MAX_COLOURS && j < originalColours; j++)
            {
                free(*(dragon->colours + j));
                *(dragon->colours + j) = NULL;
            }
            dragon->numColours = newColours;
            return;
        }

        newColours++;
        if (newColours > originalColours)
        {
            *(dragon->colours + i) = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!*(dragon->colours + i))
            {
                fprintf(stderr,"Error: failed to allocate memory for a dragon's colour\n");
                getchar();
                exit(-1);
            }
        }
        strcpy(*(dragon->colours + i), colour);
    }
    dragon->numColours = newColours;
}

static void stringToUppercase(char *const str)
{
    for (char *ix = str; *ix != '\0'; ix++)
    {
        *ix = toupper(*ix);
    }
}
