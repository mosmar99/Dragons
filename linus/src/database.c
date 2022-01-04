#include "database.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Error strings used in error messages
#define ERROR_STRING_DATABASE_CREATE "Error: failed to allocate memory for database."
#define ERROR_STRING_DATABASE_ARRAY "Error: failed to allocate memory for dragon array."
#define ERROR_STRING_DATABASE_IX_ARRAY "Error: failed to allocate memory for dragon indexes array"
#define ERROR_STRING_ID "Error: non-valid ID: "

// Returns whether or not the string entered by user is an integer or name
static bool isID(const char *const str);

// Delete a dragon by array index
// If not last, copies dragon at index + 1
// Returns true if dragon was last in array
// Parameters: (a database), (the array-index of a dragon)
static bool deleteDragon(Database *const, const unsigned int *const);

Database *createDatabase()
{
    Database *db = malloc(sizeof(Database));
    if (db == NULL)
    {
        fprintf(stderr, "%s\n", ERROR_STRING_DATABASE_CREATE);
        return NULL;
    }

    db->capacity = INITIAL_CAPACITY;
    db->nextId = 1; // id = 0 not allowed
    db->size = 0;
    db->dragons = calloc(INITIAL_CAPACITY, sizeof(Dragon));
    if (db->dragons == NULL)
    {
        fprintf(stderr, "%s\n", ERROR_STRING_DATABASE_ARRAY);
        return NULL;
    }

    return db;
}

void expandCapacity(Database *const db)
{
    Dragon *newDragonArray = calloc(GROWTH_FACTOR * db->capacity, sizeof(Dragon));
    if (!newDragonArray)
    {
        fprintf(stderr, "%s\n", ERROR_STRING_DATABASE_ARRAY);
        getchar();
        exit(-1);
    }

    // copy all dragons and free the old dragons
    for (size_t dragonIx = 0; dragonIx < db->capacity; dragonIx++)
    {
        copyDragon(&newDragonArray[dragonIx], &db->dragons[dragonIx]);

        // free dragon in old array
        free(db->dragons[dragonIx].name);
        db->dragons[dragonIx].name = NULL;
        freeColours(&db->dragons[dragonIx], 0, MAX_COLOURS - 1);
    }
    free(db->dragons);

    db->dragons = newDragonArray;
    db->capacity = GROWTH_FACTOR * db->capacity;
}

void destroyDatabase(Database *db)
{
    // free memory claimed by all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // free dragon name
        free(db->dragons[dragonIndex].name);
        db->dragons[dragonIndex].name = NULL;

        // free all colours of a dragon
        freeColours(&db->dragons[dragonIndex], 0, db->dragons[dragonIndex].numColours - 1);
    }

    free(db->dragons);
    db->dragons = NULL;

    free(db);
    db = NULL;
}

int *searchForDragon(const Database *const db, const char *const identifier)
{
    int *dragonIndexes = calloc(db->size, sizeof(int)); // array to store indexes of all dragons found that matches the identifier
    if (!dragonIndexes)
    {
        fprintf(stderr, "%s\n", ERROR_STRING_DATABASE_IX_ARRAY);
        exit(-1);
    }
    for (size_t i = 0; i < db->size; i++)
    {
        dragonIndexes[i] = SENTINEL;
    }

    bool isName = !isID(identifier);

    int id;
    if (!isName)
    { // convert the string to an integer
        char *endPtr;
        id = strtol(identifier, &endPtr, 0);
        if (id < 1 || idToIndex(db, id) >= db->size)
        {
            fprintf(stderr, "%s%d\n", ERROR_STRING_ID, id);
            return dragonIndexes;
        }
    }

    // search for a match
    unsigned int counter = 0;
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        if (isName)
        {
            if (strcmp(db->dragons[dragonIndex].name, identifier) == 0)
            {
                dragonIndexes[counter++] = idToIndex(db, db->dragons[dragonIndex].id);
            }
        }
        else
        {
            if (db->dragons[dragonIndex].id == id)
            {
                dragonIndexes[counter++] = idToIndex(db, db->dragons[dragonIndex].id);
                break; // a dragon's ID is ALWAYS unique and never reused
            }
        }
    }
    return dragonIndexes;
}

static bool isID(const char *const identifier)
{
    for (const char *i = identifier; *i != '\0'; i++)
    {
        unsigned int c = (int)*i;     // convert a character to its ASCII value in decimals
        if (!isdigit(c) && *i != '-') // only non-digit allowed in a number is '-'
        {
            return false;
        }
    }
    return true;
}

void getDatabaseInfo(const Database *const db, size_t *const max, size_t *const min, size_t *const volant, size_t *const nonVolant)
{
    assert(db->size > 0);
    *max = db->dragons[0].fierceness;
    *min = db->dragons[0].fierceness;
    *volant = 0;
    *nonVolant = 0;

    // loop all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // check max
        if (db->dragons[dragonIndex].fierceness > *max)
        {
            *max = db->dragons[dragonIndex].fierceness;
        }

        // check min
        if (db->dragons[dragonIndex].fierceness < *min)
        {
            *min = db->dragons[dragonIndex].fierceness;
        }

        // check volant
        if (db->dragons[dragonIndex].isVolant == 'Y')
        {
            (*volant)++;
        }
        else
        {
            assert(db->dragons[dragonIndex].isVolant == 'N');
            (*nonVolant)++;
        }
    }
}

int idToIndex(const Database *const db, const unsigned int id)
{
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        if (db->dragons[dragonIndex].id == id)
        {
            return dragonIndex;
        }
    }
    return -1;
}

static bool deleteDragon(Database *const db, const unsigned int *const arrayIx)
{
    /*
        if not last dragon in array
            copy next dragon
        if last dragon in array
            free all memory occupied by dragon
            decrement db size
    */
    if (db->size == 0)
    {
        return true; // do nothing if database is empty
    }

    bool isDragonLast = *arrayIx == db->size - 1 ? true : false;
    if (!isDragonLast)
    {
        copyDragon(&db->dragons[*arrayIx], &db->dragons[*arrayIx + 1]);
    }
    else
    {
        // free name
        free(db->dragons[*arrayIx].name);
        db->dragons[*arrayIx].name = NULL;

        // free all colours
        freeColours(&db->dragons[*arrayIx], 0, MAX_COLOURS - 1);

        db->size--;
    }
    return isDragonLast;
}

void doDeleteDragon(Database *const db, int ix)
{
    // Delete the dragon by repeatedly copying dragons 1 step left and lastly freeing
    // memory of the last dragon (which has by then copied 1 step left in array)
    while (!deleteDragon(db, &ix))
    {
        ix++;
    }
}

void sortDragons(Database *db, const bool sortByName)
{
    // Bubblesort
    for (size_t i = 0; i < db->size - 1; i++)
    {
        for (size_t j = 0; j < db->size - i - 1; j++)
        {
            if (sortByName)
            {
                if (strcmp(db->dragons[j].name, db->dragons[j + 1].name) > 0)
                {
                    swapDragons(&db->dragons[j], &db->dragons[j + 1]);
                }
            }
            else
            {
                if (db->dragons[j].id > db->dragons[j + 1].id)
                {
                    swapDragons(&db->dragons[j], &db->dragons[j + 1]);
                }
            }
        }
    }
}

bool dragonsHasID(const Database *const db, const unsigned int *const ixs, unsigned int id)
{
    for (size_t dragonIx = 0; dragonIx < db->size; dragonIx++) // loop all dragons
    {
        for (size_t ixsIx = 0; ixsIx < db->size; ixsIx++) // loop all indexes in ixs
        {
            if (ixs[ixsIx] == dragonIx && db->dragons[dragonIx].id == id)
            {
                return true;
            }
        }
    }

    return false;
}

void freeIxArray(int *ixArray)
{
    free(ixArray);
    ixArray = NULL;
}
