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
    db->nextId = 1; // indexing of dragons begins at index 1
    db->size = 0; // amount of dragons
    db->dragons = calloc(INITIAL_CAPACITY, sizeof(Dragon));
    if (db->dragons == NULL)
    {
        puts("Error: failed to allocate memory for dragon array.");
        return NULL;
    }

    return db;
}

void expandCapacity(Database *const db)
{
    Dragon *newDragonArray = calloc(GROWTH_FACTOR * db->capacity, sizeof(Dragon));
    if (!newDragonArray)
    {
        puts("Error: failed to allocate memory for expanded dragon array.");
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
        for (size_t i = 0; i < MAX_COLOURS; i++)
        {
            free(*(db->dragons[dragonIx].colours + i));
            *(db->dragons[dragonIx].colours + i) = NULL;
        }
    }
    free(db->dragons);

    db->dragons = newDragonArray;
    db->capacity = GROWTH_FACTOR * db->capacity;
}

void getDatabaseFilename(char *filename)
{
    printf("Enter the name of the database: ");
    scanf("%49s", filename);
}

void destroyDatabase(Database *db)
{
    if (db != NULL)
    {
        // MISSION: Free all allocated memory, 
        for (int drgIdx = 0; drgIdx < (*db).size ; drgIdx++) { // (*db).size = dragonCount
            // free calloc for name found in filehandler.c
            free((*db).dragons[drgIdx].name), (*db).dragons[drgIdx].name = NULL;

            // free all allocated space for all colours corresponding to each individual dragon
            for (int clrIdx = 0; clrIdx < (*db).dragons[drgIdx].numColours; clrIdx++) {
                free((*db).dragons[drgIdx].colours[clrIdx]), (*db).dragons[drgIdx].colours[clrIdx] = NULL;
            }
        }

        free(db);
        db = NULL;
    }
}