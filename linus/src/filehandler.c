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
    fscanf(filePtr, "%llu", &db->size);

    for (size_t dragonIndex = 0; dragonIndex < db->size && !feof(filePtr); dragonIndex++) // loop through all dragons
    {
        // read id
        fscanf(filePtr, "%llu", &db->dragons[dragonIndex].id);
        assert(db->dragons[dragonIndex].id > 0);

        // read name
        db->dragons[dragonIndex].name = calloc(MAX_NAME, sizeof(char));
        if (!db->dragons[dragonIndex].name)
        {
            puts("Error: failed to allocate memory for a dragon's name.");
            exit(-1);
        }
        fscanf(filePtr, "%49s", db->dragons[dragonIndex].name);

        // read volant
        fscanf(filePtr, "%s", &db->dragons[dragonIndex].isVolant);
        assert(db->dragons[dragonIndex].isVolant == 'Y' || db->dragons[dragonIndex].isVolant == 'N');

        // read fierceness
        fscanf(filePtr, "%llu", &db->dragons[dragonIndex].fierceness);
        assert(db->dragons[dragonIndex].fierceness >= 1 && db->dragons[dragonIndex].fierceness <= 10);

        // read # of colours
        fscanf(filePtr, "%llu", &db->dragons[dragonIndex].numColours);
        assert(db->dragons[dragonIndex].numColours <= MAX_COLOURS);

        // all the colours
        for (size_t i = 0; i < db->dragons[dragonIndex].numColours && i < MAX_COLOURS && !feof(filePtr); i++)
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
    } // end dragon loop

    // last thing to read in txt file is the next available id
    if (feof(filePtr))
    {
        puts("Error: nextId in database does not exist.");
        exit(-1);
    }
    fscanf(filePtr, "%llu", &db->nextId);

    fclose(filePtr);
}

void saveDatabase(char *filename, Database *db)
{
}