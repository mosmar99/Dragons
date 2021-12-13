#include "database.h"
#include "dragon.h"
#include "filehandler.h"
#include "userinterface.h"

/*
/opt/homebrew/bin/gcc-11 -fdiagnostics-color=always -g mahmut/src/*.c -I mahmut/include -o /Users/mahmut/Desktop/ai/c/labs/lab3/mahmut/bin/main

./mahmut/bin/main

mahmut/files/Dragons.txt
*/

int main()
{
    char filename[MAX_FILENAME - 1];
    Database *database = createDatabase();
    getDatabaseFilename(filename);
    loadDatabase(filename, database);
    printWelcomeMessage();
    puts("");
    printMenu();
    executeCommands(database);
    saveDatabase(filename, database);
    destroyDatabase(database);

    return 0;
}

