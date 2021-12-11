#include "database.h"
#include "dragon.h"
#include "filehandler.h"
#include "userinterface.h"

int main()
{
    char filename[MAX_FILENAME - 1];

    Database *database = createDatabase();
    getDatabaseFilename(filename);
    loadDatabase(filename, database);
    saveDatabase(filename, database); // needed to initialize and store the original filename in the static variable

    puts("");
    printWelcomeMessage();
    puts("");
    printMenu();
    executeCommands(database);

    saveDatabase(filename, database);
    destroyDatabase(database);
}