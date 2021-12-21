#include "database.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Returns whether or not the string entered by user is an integer or name
static bool isID(const char *const str);

Database *createDatabase()
{
    Database *db = malloc(sizeof(Database));
    if (db == NULL)
    {
        fprintf(stderr,"Error: failed to allocate memory for database.\n");
        return NULL;
    }

    db->capacity = INITIAL_CAPACITY;
    db->nextId = 1; // id = 0 not allowed
    db->size = 0;
    db->dragons = calloc(INITIAL_CAPACITY, sizeof(Dragon));
    if (db->dragons == NULL)
    {
        fprintf(stderr,"Error: failed to allocate memory for dragon array.\n");
        return NULL;
    }

    return db;
}

void expandCapacity(Database *const db)
{
    Dragon *newDragonArray = calloc(GROWTH_FACTOR * db->capacity, sizeof(Dragon));
    if (!newDragonArray)
    {
        fprintf(stderr,"Error: failed to allocate memory for expanded dragon array.\n");
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

int searchForDragon(const Database *const db, const char *const identifier)
{
    bool isName = !isID(identifier);

    int id;
    if (!isName) // convert the string to an integer
    {
        char *endPtr;
        id = strtol(identifier, &endPtr, 0);
        if (id < 1 || idToIndex(db, &id) >= db->size)
        {
            fprintf(stderr,"Error: non-valid ID: %d\n", id);
            fprintf(stderr,"Error: dragon not found\n");
            return -1;
        }
    }

    // search for a match
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        if (isName)
        {
            if (strcmp(db->dragons[dragonIndex].name, identifier) == 0)
            {
                return idToIndex(db, &db->dragons[dragonIndex].id);
            }
        }
        else
        {
            if (db->dragons[dragonIndex].id == id)
            {
                return idToIndex(db, &db->dragons[dragonIndex].id);
            }
        }
    }
    return id;
}

static bool isID(const char *const identifier)
{
    for (const char *i = identifier; *i != '\0'; i++)
    {
        unsigned int c = (int)*i; // convert a character to its ASCII value in decimals
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

int idToIndex(const Database *const db, const unsigned int *const id)
{
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        if (db->dragons[dragonIndex].id == *id)
        {
            return dragonIndex;
        }
    }
    return -1;
}

bool deleteDragon(Database *const db, const unsigned int *const arrayIx)
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
