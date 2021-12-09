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

void getDatabaseFilename(char *filename)
{
    printf("Enter the name of the database: ");
    scanf("%49s", filename);
}

void destroyDatabase(Database *db)
{
    if (db != NULL)
    {
        free(db);
        db = NULL;
    }
}