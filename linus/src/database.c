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
    // free memory claimed by all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // free dragon name
        free(db->dragons[dragonIndex].name);
        db->dragons[dragonIndex].name = NULL;

        // free all colours of a dragon
        for (size_t colourIndex = 0; colourIndex < db->dragons[dragonIndex].numColours; colourIndex++)
        {
            free(db->dragons[dragonIndex].colours[colourIndex]);
            db->dragons[dragonIndex].colours[colourIndex] = NULL;
        }
    }

    free(db->dragons);
    db->dragons = NULL;

    free(db);
    db = NULL;
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

bool deleteDragon(Database *const db, const unsigned int *const arrayIx)
{
    /*
        if not last dragon in array
            copy next dragon
        if last dragon in array
            free all memory occupied by dragon
            decrement db size
    */
    if (!db->size)
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
        for (size_t colourIx = 0; colourIx < MAX_COLOURS; colourIx++)
        {
            free(db->dragons[*arrayIx].colours[colourIx]);
            db->dragons[*arrayIx].colours[colourIx] = NULL;
        }

        db->size--;
    }
    return isDragonLast;
}

void sortDragons(Database *db, bool sortByName)
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

void swapDragons(Dragon *d1, Dragon *d2)
{
    
}

void copyDragon(Dragon *dest, Dragon *src)
{
    // copy name
    strcpy(dest->name, src->name);

    // copy id
    dest->id = src->id;

    // copy volant
    dest->isVolant = src->isVolant;

    // copy fierceness
    dest->fierceness = src->fierceness;

    // copy numColours
    dest->numColours = src->numColours;

    // copy all colours
    size_t colourIx = 0;
    for (; colourIx < dest->numColours; colourIx++)
    {
        // allocate memory if needed
        if (!dest->colours[colourIx])
        {
            dest->colours[colourIx] = calloc(MAX_COLOURS, sizeof(char));
            if (!dest->colours[colourIx])
            {
                puts("Error: failed to allocate memory for a dragon's colour.");
                exit(-1);
            }
        }
        // then copy a colour
        strcpy(dest->colours[colourIx], src->colours[colourIx]);
    }

    // delete any extra colours left behind by the now copied-over dragon
    for (; colourIx < MAX_COLOURS; colourIx++)
    {
        free(dest->colours[colourIx]);
        dest->colours[colourIx] = NULL;
    }
}
