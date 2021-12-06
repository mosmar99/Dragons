#ifndef _DRAGON_H
#define _DRAGON_H

#define MAX_COLOURS 5
typedef struct Dragon {
    unsigned int id;
    char *name;
    char isVolant;
    unsigned int fierceness;
    unsigned int numColours;
    char *colours[MAX_COLOURS];
} Dragon;


#endif