#include "database.h"
#include "dragon.h"
#include "filehandler.h"
#include "userinterface.h"

int main()
{

    Database *db = createDatabase();
    db->dragons = calloc(2, sizeof(Dragon));
    db->nextId = 3;
    db->size = 2;

    db->dragons[0].name = calloc(MAX_NAME, sizeof(char));
    strcpy(db->dragons[0].name, "TEST");
    db->dragons[0].fierceness = 1;
    db->dragons[0].id = 1;
    db->dragons[0].isVolant = 'Y';
    db->dragons[0].numColours = 4;
    for (size_t i = 0; i < db->dragons[0].numColours; i++)
    {
        *(db->dragons[0].colours + i) = calloc(MAX_COLOUR_NAME, sizeof(char));
    }
    strcpy(*(db->dragons[0].colours + 0), "RED");
    strcpy(*(db->dragons[0].colours + 1), "BLUE");
    strcpy(*(db->dragons[0].colours + 2), "GREEN");
    strcpy(*(db->dragons[0].colours + 3), "YELLOW");
    //strcpy(*(db->dragons[0].colours + 4), "PINK");

    db->dragons[1].name = calloc(MAX_NAME, sizeof(char));
    strcpy(db->dragons[1].name, "HEJ");
    db->dragons[1].fierceness = 7;
    db->dragons[1].id = 2;
    db->dragons[1].isVolant = 'N';
    db->dragons[1].numColours = 2;
    for (size_t i = 0; i < db->dragons[1].numColours; i++)
    {
        *(db->dragons[1].colours + i) = calloc(MAX_COLOUR_NAME, sizeof(char));
    }
    strcpy(*(db->dragons[1].colours + 0), "PURPLE");
    strcpy(*(db->dragons[1].colours + 1), "BLACK");
    //strcpy(*(db->dragons[1].colours + 2), "WHITE");
    //strcpy(*(db->dragons[1].colours + 3), "YELLOW");
    //strcpy(*(db->dragons[1].colours + 4), "PINK");

    swapDragons(&db->dragons[0], &db->dragons[1]);

    /*
    char filename[MAX_FILENAME - 1];

    Database *database = createDatabase();
    if (!database)
    {
        getchar();
        exit(-1);
    }
    
    getDatabaseFilename(filename);
    loadDatabase(filename, database);
    saveDatabase(filename, database); // needed to initialize and store the original filename in the static variable

    puts("");
    printWelcomeMessage();
    puts("");
    printMenu();
    executeCommands(database);

    saveDatabase(NULL, database);
    destroyDatabase(database);
    */
}