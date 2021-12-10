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

void getDatabaseFilename(char *filename)
{
    printf("Enter the name of the database: ");
    scanf("%49s", filename);
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

        free(db);
        db = NULL;
    }
}