#include "database.h"

Database *createDatabase()
{
    Database *db = malloc(sizeof(Database));
    if (db == NULL)
    {
        puts("Error: failed to allocate memory for database.");
        return NULL;
    }

    db->capacity = INITIAL_CAPACITY;
    db->nextId = 1; // id = 0 not allowed
    db->size = 0;
    db->dragons = calloc(INITIAL_CAPACITY, sizeof(Dragon));
    if (db->dragons == NULL)
    {
        puts("Error: failed to allocate memory for dragon array.");
        return NULL;
    }

    return db;
}

void destroyDatabase(Database *db)
{
    if (db != NULL)
    {
        // free memory claimed by all dragons
        for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
        {
            // free dragon name
            if (db->dragons[dragonIndex].name != NULL)
            {
                free(db->dragons[dragonIndex].name);
                db->dragons[dragonIndex].name = NULL;
            }

            // free all colours of a dragon
            for (size_t colourIndex = 0; colourIndex < db->dragons[dragonIndex].numColours; colourIndex++)
            {
                if (db->dragons[dragonIndex].colours[colourIndex] != NULL)
                {
                    free(db->dragons[dragonIndex].colours[colourIndex]);
                    db->dragons[dragonIndex].colours[colourIndex] = NULL;
                }
            }
        }

        free(db->dragons);

        free(db);
        db = NULL;
    }
}

int searchForDragon(const Database *const db, const char *identifier)
{
    bool isName = !isID(identifier);

    int id;
    if (!isName) // convert the string to an integer
    {
        char *endPtr;
        id = strtol(identifier, &endPtr, 0);
        if (id < 1 || idToIndex(db, &id) >= db->size)
        {
            printf("Error: non-valid ID: %d\n", id);
            puts("Error: dragon not found");
            return -1;
        }
    }

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

bool isID(const char *const identifier)
{
    for (const char *i = identifier; *i != '\0'; i++)
    {
        unsigned int c = (int)*i; // convert a character to its ASCII value in decimals
        if (!isdigit(c) && *i != '-')
        {
            return false;
        }
    }
    return true;
}

void getDatabaseInfo(const Database *const db, size_t *const max, size_t *const min, size_t *const volant, size_t *const nonVolant)
{
    if (db->size == 0)
    {
        puts("No dragons in database.");
        return;
    }

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
