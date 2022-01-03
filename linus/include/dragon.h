#ifndef _DRAGON_H
#define _DRAGON_H

#include <stdlib.h>

// Error strings used as error messages
#define ERROR_STRING_VOLANT "Error: invalid volant input\n"
#define ERROR_STRING_FIERCE "Error: invalid range\n"
#define ERROR_STRING_DRAGON_COLOUR "Error: failed to allocate memory for dragon colour\n"
#define ERROR_STRING_DRAGON "Error: failed to allocate memory for new dragon\n"
#define ERROR_STRING_DRAGON_NAME "Error: failed to allocate memory for dragon name\n"
#define ERROR_STRING_DRAGON_NOT_FOUND "Error: dragon/s not found\n"

// The minimum and maximum fierceness allowed
#define MIN_FIERCENESS 1
#define MAX_FIERCENESS 10

// The maximum number of colours any dragon can have
#define MAX_COLOURS 5

// Maximum (minus 1) length allowed as a colour's name
#define MAX_COLOUR_NAME 20

// The maximum (minus 1) length allowed in a dragon's name
#define MAX_NAME 20

typedef struct Dragon
{
    unsigned int id;            // id
    char *name;                 // name
    char isVolant;              // 'Y' --> it is able to fly, 'N' --> it is not able to fly
    unsigned int fierceness;    // fierceness, higher => more fierce (scale of 1 to 10)
    unsigned int numColours;    // number of colours
    char *colours[MAX_COLOURS]; // which colours
} Dragon;

// Swaps two dragons
// Parameters: (a dragon), (another dragon)
void swapDragons(Dragon *const d1, Dragon *const d2);

// Free all colours of a dragon within the given indexes
// Parameters: (a dragon), (lower bound, inclusive), (higher bound, inclusive)
void freeColours(Dragon *const d, size_t, const size_t);

// Copy a dragon to another
// Parameters: (the destination dragon), (the source dragon)
void copyDragon(Dragon *const dest, const Dragon *const src);

// Allocates memory for a dragon at the indicated colour index
// Parameters: (the dragon), (the colour index)
void createNewColour(Dragon *const dragon, const size_t colourIx);

#endif