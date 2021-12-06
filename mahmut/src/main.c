#include "database.h"
#include "dragon.h"
#include "filehandler.h"
#include "userinterface.h"

void startUpTxt();
void getTxtFileName();
void getMenu();

int main(int argc, char **argv) {
    char filename[MAX_FILENAME];
    Database *database = createDatabase();
    getDatabaseFilename(filename);
    // loadDatabase(filename, database);
    // printWelcomeMessage();
    // executeCommands(database);
    // saveDatabase(filename, database);
    destroyDatabase(database);

    return 0;
}
