#ifndef _DRAGON_H
#define _DRAGON_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// The maximum number of colours any dragon can have
#define MAX_COLOURS 5

// Maximum (minus 1) length allowed as a colour's name
#define MAX_COLOUR_NAME 25

// The maximum (minus 1) length allowed in a dragon's name
#define MAX_NAME 25

typedef struct Dragon
{
    unsigned int id;            // id
    char *name;                 // name
    char isVolant;              // 'Y' --> it is able to fly, 'N' --> it is not able to fly
    unsigned int fierceness;    // fierceness, higher => more fierce (scale of 1 to 10)
    unsigned int numColours;    // number of colours
    char *colours[MAX_COLOURS]; // which colours
} Dragon;

// Update a dragon's attributes, excl. name and id
void updateDragon(Dragon *const);

// Converts a string to all uppercase
void stringToUppercase(char *const);

#endif