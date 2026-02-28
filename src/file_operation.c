/*

    file_operations.c

    Contains all file operations done by the program.
    Specifically get-set operations for the config file, user database, and species database.

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#include <stdio.h>
#include <string.h>

// Initialize config struct
#include "config_struct.h"

/*

    Getters-setters-reset idea based from my own project (Crydengo, written in JS), wherein it looks configs up from a DB (SQLite) - Elo
    https://github.com/K97i/crydengo/blob/main/src/helpers/guild-config.js

*/

/*

    getConfig()

    Gets the config from config.bin and returns the config struct.

    <return> Config struct - result of read operation, returns the saved config file </return>

*/
Config getConfig() {
    Config configRead;

    FILE *fptr;
    fptr = fopen("config.bin", "rb");

    if (fptr != NULL) {
        fread(&configRead, sizeof(Config), sizeof(configRead) / sizeof(Config), fptr);
        fclose(fptr);
    }

    return configRead;
}

/*

    setConfig()

    Saves the inputted config to config.bin

    <param> Config configWrite - New config to be written. </param>
    <return> int - Boolean if write is successful, 1 if success, 0 if fail. </return>

*/
int setConfig(const Config configWrite) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("config.bin", "wb");

    if (fptr != NULL) {
        fwrite(&configWrite, sizeof(Config), sizeof(configWrite) / sizeof(Config), fptr);
        fclose(fptr);
        flag = 1;
    }

    return flag;
}

/*

    resetConfig()

    Resets the config to defaults.

    <return> int - Boolean if write is successful, 1 if success, 0 if fail. </return>

*/
int resetConfig() {
    Config configDefaults;

    strcpy(configDefaults.administratorKey, "OVERRIDE-1234");
    strcpy(configDefaults.encryptionKey, "N0T-@3S-3NCRYPT10N");

    return setConfig(configDefaults);
}
