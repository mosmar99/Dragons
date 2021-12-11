#include "dragon.h"

void updateDragon(Dragon *const dragon)
{
    // update volant
    char volantTest;
    printf("Enter volant (Y, N): ");
    fflush(stdin);
    scanf("%c", &volantTest);
    volantTest = toupper(volantTest);
    if (volantTest != 'Y' && volantTest != 'N')
    {
        puts("Error: invalid volant input");
        puts("Default: N");
        dragon->isVolant = 'N';
    }
    else
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
        puts("Default: 1");
        dragon->fierceness = 1;
    }
    else
    {
        dragon->fierceness = fierceTest;
    }

    // update all colours
    size_t newColours = 0;
    size_t originalColours = dragon->numColours;
    for (size_t i = 0; i < MAX_COLOURS; i++)
    {
        char colour[MAX_COLOUR_NAME - 1];
        printf("Colour %llu (of %llu) (0 to stop): ", i + 1, MAX_COLOURS);
        fflush(stdin);
        scanf("%24s", colour);
        if (*colour == '0')
        {
            // free the remaining colours
            for (size_t j = i; j < MAX_COLOURS && j < originalColours; j++)
            {
                free(dragon->colours[j]);
                dragon->colours[j] = NULL;
            }
            dragon->numColours = newColours;
            return;
        }
        stringToUppercase(colour);

        newColours++;
        if (newColours > originalColours)
        {
            dragon->colours[i] = calloc(MAX_COLOUR_NAME, sizeof(char));
            if (!dragon->colours[i])
            {
                puts("Error: failed to allocate memory for a dragon's colour");
                exit(-1);
            }
        }
        strcpy(dragon->colours[i], colour);
    }
    dragon->numColours = newColours;
}

void stringToUppercase(char *const name)
{
    for (char *ix = name; *ix != '\0'; ix++)
    {
        *ix = toupper(*ix);
    }
}
