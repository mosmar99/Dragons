#include "dragon.h"

void updateDragon(Dragon *const dragon, const unsigned int *const arrayIndex)
{
    // update volant
    char volantTest;
    printf("\nEnter volant (Y, N): ");
    fflush(stdin);
    scanf("%c", &volantTest);
    volantTest = toupper(volantTest);
    if (volantTest != 'Y' && volantTest != 'N')
    {
        puts("Error: invalid volant input");
    }
    else // only update if valid input
    {
        dragon->isVolant = volantTest;
    }

    // update fierceness
    int fierceTest;
    printf("Enter fierceness (1-10): ");
    fflush(stdin);
    scanf("%2d[0123456789]", &fierceTest);
    if (fierceTest < 1 || fierceTest > 10)
    {
        puts("Error: invalid range");
    }
    else
    {
        dragon->fierceness = fierceTest;
    }

    // update all colours
    size_t numbOfColours = 0;
    for (size_t i = 0; i < MAX_COLOURS; i++)
    {
        char colour[MAX_COLOUR_NAME - 1];
        printf("Colour %llu (of %llu) (0 to stop): ", i + 1, MAX_COLOURS);
        fflush(stdin);
        scanf("%24s", colour);
        if (*colour == '0')
        {
            return;
        }
        for (char *ix = colour; *ix != '\0'; ix++)
        {
            *ix = toupper(*ix);
        }

        numbOfColours++;
        if (numbOfColours > dragon->numColours)
        {
            dragon->colours[i] = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!dragon->colours[i])
            {
                puts("Error: failed to allocate memory for a dragon's colour");
                exit(-1);
            }
            dragon->numColours = numbOfColours;
        }
        strcpy(dragon->colours[i], colour);
    }
}