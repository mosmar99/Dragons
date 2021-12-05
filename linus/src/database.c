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
    return db;
}

void getDatabaseFilename(char *filename)
{
    printf("Enter the name of the database: ");
    scanf("%49s", filename);
}

void loadDatabase(char *filename, Database *db)
{
}

void saveDatabase(char *filename, Database *db)
{
}

void destroyDatabase(Database *db)
{
    if (db != NULL)
    {
        free(db);
        db = NULL;
    }
}