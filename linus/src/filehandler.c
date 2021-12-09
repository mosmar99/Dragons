#include "filehandler.h"
#include "database.h"

void loadDatabase(char *filename, Database *db)
{
    FILE *filePtr = fopen(filename, "r");
    if (!filePtr)
    {
        printf("Error: failed to open %s.", filename);
        exit(-1);
    }

    // read how many dragons there are in the list
    size_t numbOfDragons;
    fscanf(filePtr, "%llu", &numbOfDragons);
    db->size = numbOfDragons;

    size_t dragonIndex = 0;                               // count dragons
    while (dragonIndex < numbOfDragons || !feof(filePtr)) // loop through all dragons
    {
        // read id
        size_t id;
        fscanf(filePtr, "%llu", &id);
        assert(id > 0);
        db->dragons[dragonIndex].id = id;

        // read name
        db->dragons[dragonIndex].name = calloc(MAX_NAME, sizeof(char));
        if (!db->dragons[dragonIndex].name)
        {
            puts("Error: failed to allocate memory for a dragon's name.");
            exit(-1);
        }
        fscanf(filePtr, "%49s", db->dragons[dragonIndex].name);

        // read volant
        char volant;
        fscanf(filePtr, "%s", &volant);
        assert(volant == 'Y' || volant == 'N');
        db->dragons[dragonIndex].isVolant = volant;

        // read fierceness
        size_t fierceness;
        fscanf(filePtr, "%llu", &fierceness);
        assert(fierceness >= 1 && fierceness <= 10);
        db->dragons[dragonIndex].fierceness = fierceness;

        // read # of colours
        size_t numbOfColours;
        fscanf(filePtr, "%llu", &numbOfColours);
        assert(numbOfColours <= MAX_COLOURS);
        db->dragons[dragonIndex].numColours = numbOfColours;

        // all the colours
        for (size_t i = 0; i < numbOfColours && i < MAX_COLOURS && !feof(filePtr); i++)
        {
            db->dragons[dragonIndex].colours[i] = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!db->dragons[dragonIndex].colours[i])
            {
                puts("Error: failed to allocate memory for a dragon's colour.");
                exit(-1);
            }
            fscanf(filePtr, "%24s", db->dragons[dragonIndex].colours[i]);
        }

        // at this point, one dragon has been fully read and stored in the database
        dragonIndex++;
    } // end dragon loop

    // last thing to read in txt file is the next available id
    if (feof(filePtr))
    {
        puts("Error: nextId in database does not exist.");
        exit(-1);
    }

    size_t nextId;
    fscanf(filePtr, "%llu", &nextId);
    db->nextId = nextId;

    fclose(filePtr);
}

void saveDatabase(char *filename, Database *db)
{
}