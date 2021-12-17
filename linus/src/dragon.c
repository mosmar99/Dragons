#include "dragon.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void swapDragons(Dragon *const d1, Dragon *const d2)
{
    // set up a temporary dragon
    Dragon *temp = calloc(1, sizeof(Dragon));
    if (!temp)
    {
        fprintf(stderr, "Error: failed to allocate memory for dragon\n");
        getchar();
        exit(-1);
    }

    // do the swap
    copyDragon(temp, d1);
    copyDragon(d1, d2);
    copyDragon(d2, temp);

    // clean up the temporary dragon
    free(temp->name);
    temp->name = NULL;
    freeColours(temp, 0, MAX_COLOURS - 1);
    free(temp);
    temp = NULL;
}

void copyDragon(Dragon *const dest, const Dragon *const src)
{
    // copy name
    if (!dest->name)
    { // allocate memory if needed
        dest->name = calloc(MAX_NAME, sizeof(char));
        if (!dest->name)
        {
            fprintf(stderr, "Error: failed to allocate memory for dragon name.\n");
            getchar();
            exit(-1);
        }
    }
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
        if (!*(dest->colours + colourIx))
        {
            *(dest->colours + colourIx) = calloc(MAX_COLOURS, sizeof(char));
            if (!*(dest->colours + colourIx))
            {
                
                fprintf(stderr, "Error: failed to allocate memory for a dragon's colour.\n");
                getchar();
                exit(-1);
            }
        }
        // then copy a colour
        strcpy(*(dest->colours + colourIx), *(src->colours + colourIx));
    }

    // free any extra colours left behind by the now copied-over dragon
    freeColours(dest, colourIx, MAX_COLOURS - 1);
}

void freeColours(Dragon *dragon, size_t lower, const size_t higher)
{
    assert(higher < MAX_COLOURS);
    for (; lower <= higher; lower++)
    {
        free(*(dragon->colours + lower));
        *(dragon->colours + lower) = NULL;
    }
}
