#include "filehandler.h"
#include "database.h"

void loadDatabase(char *filename, Database *db)
{
    FILE *filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("Error: failed to open %s.", filename);
        exit(-1);
    }

    // read how many dragons there are in the list
    size_t numbOfDragons;
    fscanf(filePtr, "%llu", &numbOfDragons);
    db->size = numbOfDragons;

    size_t dragonIndex = 0;  // count dragons
    size_t integersRead = 0; // always read 3 integers per dragon (id, fierce, # of colours)
    bool hasReadName = false;
    bool hasReadVolant = false;
    size_t numbOfColours;
    while (dragonIndex < numbOfDragons || !feof(filePtr)) // loop through all dragons
    {
        if (integersRead == 0) // read id
        {
            size_t id;
            fscanf(filePtr, "%llu", &id);
            db->dragons[dragonIndex].id = id;
            integersRead++;
        }
        else if (!hasReadName) // read name
        {
            char name[MAX_NAME - 1];
            fscanf(filePtr, "%49s", name);
            db->dragons[dragonIndex].name = name;
            hasReadName = true;
        }
        else if (!hasReadVolant) // read volant
        {
            char volant;
            fscanf(filePtr, "%s", &volant);
            assert(volant == 'Y' || volant == 'N');
            db->dragons[dragonIndex].isVolant = volant;
            hasReadVolant = true;
        }
        else if (integersRead == 1) // read fierceness
        {
            size_t fierceness;
            fscanf(filePtr, "%llu", &fierceness);
            db->dragons[dragonIndex].fierceness = fierceness;
            integersRead++;
        }
        else if (integersRead == 2) // read # of colours
        {
            fscanf(filePtr, "%llu", &numbOfColours);
            assert(numbOfColours <= MAX_COLOURS);
            db->dragons[dragonIndex].numColours = numbOfColours;
            integersRead++;
        }
        else // all the colours
        {

            for (size_t i = 0; i < numbOfColours && i < MAX_COLOURS && !feof(filePtr); i++)
            {
                char colour[MAX_COLOUR_NAME - 1];
                fscanf(filePtr, "%24s", colour);
                db->dragons[dragonIndex].colours[i] = colour;
            }

            // at this point, one dragon has been fully read and stored in the database

            // reset neccesary variables to read another dragon
            dragonIndex++;
            integersRead = 0;
            hasReadName = false;
            hasReadVolant = false;
        }
    } // end dragon loop

    // last thing to read in txt file is the next available id
    size_t nextId;
    fscanf(filePtr, "%llu", &nextId);
    db->nextId = nextId;

    fclose(filePtr);
}

void saveDatabase(char *filename, Database *db)
{
}