#include "dragon.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void copyDragon(Dragon *const dest, const Dragon *const src)
{
    // copy name
    if (!dest->name)
    { // allocate memory if needed
        dest->name = calloc(MAX_NAME, sizeof(char));
        if (!dest->name)
        {
            puts("Error: failed to allocate memory for dragon name.");
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
                puts("Error: failed to allocate memory for a dragon's colour.");
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