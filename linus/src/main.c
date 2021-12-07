#include "database.h"
#include "dragon.h"
#include "filehandler.h"
#include "userinterface.h"

int main()
{
    /*
    char filename[MAX_FILENAME];

    Database *database = createDatabase();
    getDatabaseFilename(filename);
    */

    printWelcomeMessage();
    puts("");
    printMenu();
    executeCommands();
}