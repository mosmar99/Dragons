#include "userinterface.h"
#include "filehandler.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// constants used for formatting when printing dragon/s
#define IDWIDTH 5
#define NAMEWIDTH MAX_NAME
#define VOLANTWIDTH 6
#define FIERCENESSWIDTH 10
#define NUMCOLOURSWIDTH 8
#define COLOURSWIDTH MAX_COLOURS *MAX_COLOUR_NAME

// Prints a list of dragons (Database), (array of dragons' indexes), (true = all dragons, false = some dragons), (true = detailed, false = breif)
static void listDragons(const Database *const db, const unsigned int *const ixs, bool all, bool detailed);

// Get an ID or name of dragon from user
static void getDragonNameOrId(char *const str);

// Prints one dragon based on array index, detailed or brief
static void printOneDragonStats(const Database *const db, unsigned int ix, bool detailed);

// Prints statistics of the database
static void printDatabaseInfo(const Database *const db);

// Handles updating a dragon
static void updateDragonHandler(Database *const db);

// Handles inserting a new dragon
static void insertDragonHandler(Database *const db);

// Handles deleting a dragon
static void deleteDragonHandler(Database *const db);

// Handles sorting the database
static void sortDragonsHandler(Database *const db);

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

// Prompts the user for an identifier and prints that dragon in detail
static void listOneDragon(const Database *const db);

// Prompts user to select 1 dragon if multiple dragons were found
// Select 1 dragon by ID and returns its array index
static int selectOneDragon(const Database *const db, const unsigned int *const ixs);

void printWelcomeMessage()
{
    puts("This program helps organize information about dragons. You may add and");
    puts("remove dragons and their attributes, list the dragons currently in the");
    puts("database, and their attributes, look up the attributes of an individual");
    puts("dragon, get statistics from the database, or sort the database.");
}

void printMenu()
{
    puts("\n------------------------------------------");
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
        scanf("%d[-012345678]", &choice);

        switch (choice)
        {
        case 0:
            printMenu();
            break;
        case 1:
            insertDragonHandler(db);
            break;
        case 2:
            updateDragonHandler(db);
            break;
        case 3:
            deleteDragonHandler(db);
            break;
        case 4:
            listDragons(db, NULL, true, false); // brief
            break;
        case 5:
            listDragons(db, NULL, true, true); // detailed
            break;
        case 6:
            listOneDragon(db);
            break;
        case 7:
            printDatabaseInfo(db);
            break;
        case 8:
            sortDragonsHandler(db);
            break;
        case -1:
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

static void listDragons(const Database *const db, const unsigned int *const ixs, bool all, bool detailed)
{
    assert(!(ixs == NULL && all == false)); // if not all dragons, use indexes from ixs array

    puts("");
    puts("--------------------------------------------------------------------------------");
    printf("%*s  %-*s", IDWIDTH, "ID", NAMEWIDTH, "Name");
    if (detailed)
    {
        printf("%s  %*s  %*s  %-*s\n", "Volant", FIERCENESSWIDTH, "Fierceness",
               NUMCOLOURSWIDTH, "#Colours", COLOURSWIDTH, "Colours");
    }
    else
    {
        puts("");
    }
    puts("--------------------------------------------------------------------------------");

    // loop through dragon array
    unsigned int counter = 0;
    for (size_t i = 0; i < db->size; i++)
    {
        if (all || i == ixs[counter])
        {
            printOneDragonStats(db, i, detailed);
            if (!all)
            {
                counter++;
            }
        }
    }
}

static void getDragonNameOrId(char *const identifier)
{
    printf("\nEnter ID or name of dragon: ");
    fflush(stdin);
    scanf("%19s", identifier);
    stringToUppercase(identifier);
}

static void printOneDragonStats(const Database *const db, unsigned int ix, bool detailed)
{
    // print id
    printf("%*llu", IDWIDTH, db->dragons[ix].id);

    // print name
    printf("  %-*s", NAMEWIDTH, db->dragons[ix].name);

    if (detailed)
    {
        // print volant
        printf("%*c", VOLANTWIDTH, db->dragons[ix].isVolant);

        // print fierceness
        printf("  %*llu", FIERCENESSWIDTH, db->dragons[ix].fierceness);

        // print # of colours
        printf("  %*llu ", NUMCOLOURSWIDTH, db->dragons[ix].numColours);

        // print all colours
        for (size_t i = 0; i < db->dragons[ix].numColours; i++)
        {
            printf(" %s", *(db->dragons[ix].colours + i));
        }
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
    printf("%*s  %*s  %*s  %*s  %*s\n", sizeWidth, "Size", fiercenessWidth, "MinFierceness",
           fiercenessWidth, "MaxFierceness", volantWidth, "#Volant", nonVolantWidth, "#NonVolant");
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

static void updateDragonHandler(Database *const db)
{
    if (db->size == 0)
    {
        fprintf(stderr, "%s", ERROR_STRING_DATABASE_EMPTY);
        return;
    }

    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int *indexes = searchForDragon(db, identifier);
    if (*indexes == SENTINEL)
    {
        fprintf(stderr, "%s", ERROR_STRING_DRAGON_NOT_FOUND);
        return;
    }

    int ix = *indexes;
    if (*(indexes + 1) != SENTINEL) // multiple dragons were found
    {
        ix = selectOneDragon(db, indexes);
    }

    puts("");
    updateDragon(&db->dragons[ix]);

    freeIntegerArray(indexes); // free the array created by searchForDragon()

    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon updated.");
}

static void insertDragonHandler(Database *const db)
{
    // check if it's needed to expand database capacity
    if (db->size == db->capacity)
    {
        expandCapacity(db);
        saveDatabase(NULL, db);
        loadDatabase(NULL, db);
    }

    // prompt name
    puts("");
    char name[MAX_NAME - 1];
    do
    {
        printf("Enter name: ");
        fflush(stdin);
        scanf("%19s", name);
        if (!checkNameOrColour(name))
        {
            fprintf(stderr, "%s", ERROR_STRING_COLOUR_VALID);
        }
    } while (!checkNameOrColour(name));
    stringToUppercase(name);

    // assign id
    db->dragons[db->size].id = db->nextId++;
    const int ix = idToIndex(db, &db->dragons[db->size++].id);
    assert(ix >= 0);

    // assign name
    createName(db, name, ix);

    // assign rest of the attributes
    updateDragon(&db->dragons[ix]);
    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon inserterd.");
}

static void deleteDragonHandler(Database *const db)
{
    if (db->size == 0)
    {
        fprintf(stderr, "%s", ERROR_STRING_DATABASE_EMPTY);
        return;
    }

    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int *indexes = searchForDragon(db, identifier);
    if (*indexes == SENTINEL)
    {
        fprintf(stderr, "%s", ERROR_STRING_DRAGON_NOT_FOUND);
        return;
    }

    int ix = *indexes;
    if (*(indexes + 1) != SENTINEL) // multiple dragons were found
    {
        ix = selectOneDragon(db, indexes);
    }

    doDeleteDragon(db, ix);

    freeIntegerArray(indexes); // free the array created by searchForDragon()

    saveDatabase(NULL, db);
    loadDatabase(NULL, db);
    puts("Dragon deleted.");
}

static void sortDragonsHandler(Database *const db)
{
    if (db->size <= 1) // pointless to sort empty array or array of size 0 or 1
    {
        fprintf(stderr, "%s", "No need to sort a database with no more than 1 dragon.\n");
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
        // prompt colour
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

        if (*colour != '\n') // remove breakline due to fgets()
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
        { // if user wants to end colour input, free all remaining colours
            *colour = 0;
            freeColours(dragon, i, MAX_COLOURS - 1);
            dragon->numColours = newColours;
            return;
        }

        newColours++;
        if (newColours > originalColours) // if needed, create new space for new colour
        {
            createNewColour(dragon, i);
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

static void listOneDragon(const Database *const db)
{
    char identifier[MAX_NAME - 1];
    getDragonNameOrId(identifier);
    int *indexes = searchForDragon(db, identifier);
    if (*indexes == SENTINEL)
    {
        fprintf(stderr, "%s", ERROR_STRING_DRAGON_NOT_FOUND);
        return;
    }
    if (*(indexes + 1) != SENTINEL) // multiple dragons were found
    {
        int index = selectOneDragon(db, indexes);

        // reset the index array as if only one dragon was found
        *indexes = index;
        for (size_t i = 1; i < db->size; i++)
        {
            *(indexes + i) = SENTINEL;
        }
    }

    // list 1 dragon
    listDragons(db, indexes, false, true);

    freeIntegerArray(indexes); // free the array created by searchForDragon()
}

static int selectOneDragon(const Database *const db, const unsigned int *const ixs)
{
    puts("\nMultiple dragons were found. Select one by ID.");
    listDragons(db, ixs, false, false);
    unsigned int id;
    do
    {
        printf("\n%s", "?: ");
        fflush(stdin);
        scanf("%hu[0123456789]", &id);
        if (!dragonsHasID(db, ixs, id))
        {
            fprintf(stderr, "%s\n", ERROR_STRING_MENU_SELECTION);
        }
    } while (!dragonsHasID(db, ixs, id));
    return idToIndex(db, &id);
}
