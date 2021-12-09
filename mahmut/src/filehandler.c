#include "filehandler.h"
#include "database.h"

void loadDatabase(char *filename, Database *db)
{
    // read file dragon.txt, mahmut/files/dragons.txt
    FILE *drgFilePtr = fopen(filename, "r");
    if(drgFilePtr == NULL) printf("Err: File couldn't be opened, exiting the program"), exit (-1); // file couldn't be opened, so exit program

    // read dragoncount
    fscanf(drgFilePtr, "%d", &(*db).size);
    
    int id, colourCount, fierceness, nextId; char volant; // used to check validity of input
    for (int drgIdx = 0; drgIdx < (*db).size && !feof(drgFilePtr); drgIdx++) {

        // read id
        fscanf(drgFilePtr, "%d", &id), assert(id > 0); // read, save and check input
        (*db).dragons[drgIdx].id = id; // init idx to positively read input

        // read name
        (*db).dragons[drgIdx].name = calloc(MAX_NAME, sizeof(char));
        if(!(*db).dragons[drgIdx].name) puts("Err: Failed to allocate memory for dragon name"), exit(-1);
        fscanf(drgFilePtr, "%49s", (*db).dragons[drgIdx].name);

        // read volant
        fscanf(drgFilePtr, "%s", &volant), assert(volant == 'Y' || volant == 'N'); // read, check
        (*db).dragons[drgIdx].isVolant = volant;

        // read fierceness
        fscanf(drgFilePtr, "%d", &fierceness), assert(fierceness >= 1 && fierceness <= 10);
        (*db).dragons[drgIdx].fierceness = fierceness;

        // read # of colours
        fscanf(drgFilePtr, "%d", &colourCount), assert(colourCount > 0 && colourCount <= MAX_COLOURS);
        (*db).dragons[drgIdx].numColours = colourCount;

        // all the colours
        for (int currCol = 0; currCol < colourCount && currCol < MAX_COLOURS && !feof(drgFilePtr); currCol++) {
            (*db).dragons[drgIdx].colours[currCol] = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!(*db).dragons[drgIdx].colours[currCol]) puts("Err: Failed to allocate memory forc dragon color"), exit(-1);
            fscanf(drgFilePtr, "%24s", (*db).dragons[drgIdx].colours[currCol]);
        }
    } // end dragon loop

    // read next available ID for a potentially newly added dragon to our database
    if(feof(drgFilePtr)) puts("Err: nextId does not exist in database"), exit(-1);
    fscanf(drgFilePtr, "%d", &nextId);
    (*db).nextId = nextId;

    fclose(drgFilePtr);
}

void saveDatabase(char *filename, Database *db)
{
}