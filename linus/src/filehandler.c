#include "filehandler.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Error strings used in error messages
#define ERROR_STRING_FILE_OPEN "Error: failed to open"
#define ERROR_STRING_NEXTID "Error: nextId in database does not exist"

// Read ID for the dragon at dragonArray[dragonIndex]
static void readID(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read Name for the dragon at dragonArray[dragonIndex]
static void readName(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read Volant for the dragon at dragonArray[dragonIndex]
static void readVolant(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read Fierceness for the dragon at dragonArray[dragonIndex]
static void readFierceness(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read Number of colours for the dragon at dragonArray[dragonIndex]
static void readNumColours(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read all colours for the dragon at dragonArray[dragonIndex]
static void readColours(FILE *const filePtr, Database *const db, const size_t dragonIndex);

// Read next available unique ID
static void readNextID(FILE *const filePtr, Database *const db);

void loadDatabase(const char *const filename, Database *const db)
{
    static char originalFilename[MAX_FILENAME - 1];
    char filenameToUse[MAX_FILENAME - 1];
    if (filename)
    {
        strcpy(originalFilename, filename); // stores the original filename entered at start of main()
    }
    strcpy(filenameToUse, originalFilename);

    FILE *filePtr = fopen(filenameToUse, "r");
    if (!filePtr) // if .txt file doesn't exist at desired path, create new .txt file
    {
        filePtr = fopen(filenameToUse, "w");
        if (!filePtr)
        {
            fprintf(stderr, "%s %s\n", ERROR_STRING_FILE_OPEN, filenameToUse);
            getchar();
            exit(-1);
        }
    }

    // read how many dragons there are in the list
    fscanf(filePtr, "%llu", &db->size);

    // loop through all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size && dragonIndex < db->capacity && !feof(filePtr); dragonIndex++)
    {
        readID(filePtr, db, dragonIndex);

        readName(filePtr, db, dragonIndex);

        readVolant(filePtr, db, dragonIndex);

        readFierceness(filePtr, db, dragonIndex);

        readNumColours(filePtr, db, dragonIndex);

        readColours(filePtr, db, dragonIndex);

        // at this point, one dragon has been fully read and stored in the database
    }

    // last thing to read in txt file is the next available id
    readNextID(filePtr, db);

    fclose(filePtr);

    // check if the number of dragons in .txt file exceeded database capacity
    if (db->size > db->capacity)
    {
        // expand capacity and load again
        expandCapacity(db);
        loadDatabase(NULL, db);
    }
}

void saveDatabase(const char *const filename, const Database *const db)
{
    static char originalFilename[MAX_FILENAME - 1];
    char filenameToUse[MAX_FILENAME - 1];
    if (filename)
    {
        strcpy(originalFilename, filename); // stores the original filename entered at start of main()
    }
    strcpy(filenameToUse, originalFilename);

    FILE *filePtr = fopen(filenameToUse, "w");
    if (!filePtr)
    {
        fprintf(stderr, "%s %s.\n", ERROR_STRING_FILE_OPEN, filenameToUse);
        getchar();
        exit(-1);
    }

    // write database size
    fprintf(filePtr, "%llu\n", db->size);

    // loop through all dragons
    for (size_t dragonIndex = 0; dragonIndex < db->size; dragonIndex++)
    {
        // write id
        fprintf(filePtr, "%llu\n", db->dragons[dragonIndex].id);

        // write name
        fprintf(filePtr, "%s\n", db->dragons[dragonIndex].name);

        // write volant
        fprintf(filePtr, "%c\n", db->dragons[dragonIndex].isVolant);

        // write fierceness
        fprintf(filePtr, "%llu\n", db->dragons[dragonIndex].fierceness);

        // write # of colours
        fprintf(filePtr, "%llu\n", db->dragons[dragonIndex].numColours);

        // write all colours
        for (size_t colourIndex = 0; colourIndex < db->dragons[dragonIndex].numColours; colourIndex++)
        {
            fprintf(filePtr, "%s\n", db->dragons[dragonIndex].colours[colourIndex]);
        }

    } // end dragon loop

    // write next available unique id
    fprintf(filePtr, "%llu", db->nextId);

    fclose(filePtr);
}

static void readID(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    fscanf(filePtr, "%d", &db->dragons[dragonIndex].id);
    assert(db->dragons[dragonIndex].id > 0);
}

static void readName(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    db->dragons[dragonIndex].name = calloc(MAX_NAME, sizeof(char));
    if (!db->dragons[dragonIndex].name)
    {
        fprintf(stderr, "%s\n", ERROR_STRING_DRAGON_NAME);
        getchar();
        exit(-1);
    }
    fscanf(filePtr, "%19s", db->dragons[dragonIndex].name);
}

static void readVolant(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    fscanf(filePtr, "%s", &db->dragons[dragonIndex].isVolant);
    assert(db->dragons[dragonIndex].isVolant == 'Y' || db->dragons[dragonIndex].isVolant == 'N');
}

static void readFierceness(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    fscanf(filePtr, "%d", &db->dragons[dragonIndex].fierceness);
    assert(db->dragons[dragonIndex].fierceness >= MIN_FIERCENESS && db->dragons[dragonIndex].fierceness <= MAX_FIERCENESS);
}

static void readNumColours(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    fscanf(filePtr, "%d", &db->dragons[dragonIndex].numColours);
    assert(db->dragons[dragonIndex].numColours <= MAX_COLOURS);
}

static void readColours(FILE *const filePtr, Database *const db, const size_t dragonIndex)
{
    for (size_t i = 0; i < db->dragons[dragonIndex].numColours && i < MAX_COLOURS && !feof(filePtr); i++)
    {
        *(db->dragons[dragonIndex].colours + i) = calloc(MAX_COLOUR_NAME, sizeof(char));
        if (!*(db->dragons[dragonIndex].colours + i))
        {
            fprintf(stderr, "%s\n", ERROR_STRING_DRAGON_COLOUR);
            getchar();
            exit(-1);
        }
        fscanf(filePtr, "%19s", db->dragons[dragonIndex].colours[i]);
    }
}

static void readNextID(FILE *const filePtr, Database *const db)
{
    if (feof(filePtr))
    {
        fprintf(stderr, "%s\n", ERROR_STRING_NEXTID);
        getchar();
        exit(-1);
    }
    fscanf(filePtr, "%d", &db->nextId);
    assert(db->nextId > 0);
}
