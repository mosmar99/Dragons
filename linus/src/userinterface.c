#include "userinterface.h"
#include "filehandler.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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
static void updateDragon(Dragon *const dragon);

// Update a dragon's volant
static void updateVolant(Dragon *const dragon);

// Update a dragon's fierceness
static void updateFierce(Dragon *const dragon);

// Update a dragon's colours
static void updateColours(Dragon *const dragon);

// Converts a string to all uppercase
static void stringToUppercase(char *const str);

// Only letters in the english alphabet is allowed
static bool checkNameOrColour(const char *const str);

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
            fprintf(stderr, "%s", ERROR_STRING_MENU_SELECTION);
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

static void listAllDragonsBrief(const Database *const db)
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

static void listAllDragonsDetailed(const Database *const db)
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

static void getDragonNameOrId(char *const identifier)
{
    printf("\nEnter ID or name of dragon: ");
    fflush(stdin);
    scanf("%19s", identifier);
    stringToUppercase(identifier);
}

static void printOneDragon(const Database *const db)
{
    if (db->size == 0)
    {
        fprintf(stderr, "%s", ERROR_STRING_DATABASE_EMPTY);
        return;
    }

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

static void printDatabaseInfo(const Database *const db)
{
    if (db->size == 0)
    {
        puts("Database is empty.");
        return;
    }

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

static void doUpdateDragon(Database *const db)
{
    if (db->size == 0)
    {
        fprintf(stderr, "%s", ERROR_STRING_DATABASE_EMPTY);
        return;
    }

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

static void doInsertDragon(Database *const db)
{
    // check if it's needed to expand database capacity
    if (db->size == db->capacity)
    {
        expandCapacity(db);
        saveDatabase(NULL, db);
        loadDatabase(NULL, db);
    }

    // id
    db->dragons[db->size].id = db->nextId++;
    const int ix = idToIndex(db, &db->dragons[db->size++].id);
    assert(ix >= 0);

    // name
    db->dragons[ix].name = calloc(MAX_NAME, sizeof(char));
    if (!db->dragons[ix].name)
    {

        fprintf(stderr, "%s", ERROR_STRING_DRAGON_NAME);
        getchar();
        exit(-1);
    }

    puts("");
    char name[MAX_NAME - 1];
    do
    {
        printf("Enter name: ");
        fflush(stdin);
        fgets(name, MAX_NAME - 1, stdin);
        if (!checkNameOrColour(name))
        {
            fprintf(stderr, "%s", ERROR_STRING_COLOUR_VALID);
        }
    } while (!checkNameOrColour(name));

    stringToUppercase(name);
    strcpy(db->dragons[ix].name, name);

    // rest of the attributes
    updateDragon(&db->dragons[ix]);
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon inserterd.");
}

static void doDeleteDragon(Database *const db)
{
    if (db->size == 0)
    {
        fprintf(stderr, "%s", ERROR_STRING_DATABASE_EMPTY);
        return;
    }

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

static void doSortDragons(Database *const db)
{
    if (db->size <= 1) // pointless to sort empty array or array of size 0 or 1
    {
        puts("You can't sort a database with no more than 1 dragon, dummy.");
        return;
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

static void updateDragon(Dragon *const dragon)
{
    updateVolant(dragon);
    updateFierce(dragon);
    updateColours(dragon);
}

static void updateVolant(Dragon *const dragon)
{
    char volant;
    do
    {
        printf("Enter volant (Y, N): ");
        fflush(stdin);
        scanf("%c", &volant);
        volant = toupper(volant);
        if (volant != 'Y' && volant != 'N')
        {
            fprintf(stderr, "%s", ERROR_STRING_VOLANT);
        }
    } while (volant != 'Y' && volant != 'N');
    dragon->isVolant = volant;
}

static void updateFierce(Dragon *const dragon)
{
    int fierce;
    do
    {
        printf("Enter fierceness (%d-%d): ", MIN_FIERCENESS, MAX_FIERCENESS);
        fflush(stdin);
        scanf("%2d[0123456789]", &fierce);
        if (fierce < MIN_FIERCENESS || fierce > MAX_FIERCENESS)
        {
            fprintf(stderr, "%s", ERROR_STRING_FIERCE);
        }
    } while (fierce < MIN_FIERCENESS || fierce > MAX_FIERCENESS);
    dragon->fierceness = fierce;
}

static void updateColours(Dragon *const dragon)
{
    size_t newColours = 0;
    size_t originalColours = dragon->numColours;
    for (size_t i = 0; i < MAX_COLOURS; i++)
    {
        char colour[MAX_COLOUR_NAME - 1];
        do
        {
            printf("Colour (%llu of %llu): ", i + 1, MAX_COLOURS);
            fflush(stdin);
            fgets(colour, MAX_COLOUR_NAME - 1, stdin);
            if (!checkNameOrColour(colour))
            {
                fprintf(stderr, "%s", ERROR_STRING_NAME_VALID);
            }

        } while (!checkNameOrColour(colour));

        stringToUppercase(colour);

        if (*colour != '\n')
        {
            for (size_t m = 0;; m++)
            {
                if (colour[m] == '\n')
                {
                    colour[m] = 0;
                    break;
                }
            }
        }
        else
        {
            *colour = 0;
            freeColours(dragon, i, MAX_COLOURS - 1);
            dragon->numColours = newColours;
            return;
        }

        newColours++;
        if (newColours > originalColours)
        {
            *(dragon->colours + i) = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!*(dragon->colours + i))
            {
                fprintf(stderr, "%s", ERROR_STRING_DRAGON_COLOUR);
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

static bool checkNameOrColour(const char *const str)
{
    for (const char *c = str; *c != '\n' && *c != 0; c++)
    {
        if (!isalpha(*c))
        {
            return false;
        }
    }
    return true;
}
