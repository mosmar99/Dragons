#ifndef _DRAGON_H
#define _DRAGON_H

#include <stdlib.h>

// The maximum number of colours any dragon can have
#define MAX_COLOURS 5

// Maximum (minus 1) length allowed as a colour's name
#define MAX_COLOUR_NAME 25

// The maximum (minus 1) length allowed in a dragon's name
#define MAX_NAME 50

typedef struct Dragon
{
    unsigned int id;            // id
    char *name;                 // name
    char isVolant;              // 'Y' --> it is able to fly, 'N' --> it is not able to fly
    unsigned int fierceness;    // fierceness, higher => more fierce
    unsigned int numColours;    // number of colours
    char *colours[MAX_COLOURS]; // which colours
} Dragon;

// Free all colours of a dragon within the given indexes
void freeColours(Dragon *dragon, size_t lower, const size_t higher);

// Copy a dragon to another
void copyDragon(Dragon *const dest, const Dragon *const src);

#endif