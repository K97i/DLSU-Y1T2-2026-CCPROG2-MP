/*

    file_operations.c

    Contains all file operations done by the program.
    Specifically get-set operations for the config file, user database, and species database.

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-3-2026

*/

#include <stdio.h>
#include <string.h>

// Initialize structs
#include "config_struct.h"
#include "user_struct.h"

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
    Config configRead = { 0 };

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

/*

    getAllUsers()

    Gets all users from DB

*/

void getAllUsers(User array[USER_LIMIT]) {
    User users[USER_LIMIT] = { 0 };

    FILE *fptr;
    fptr = fopen("users.bin", "rb");

    if (fptr != NULL) {
        fread(&users, sizeof(User), USER_LIMIT, fptr);
        fclose(fptr);
    }

    for (int i = 0; i < USER_LIMIT ; i++)
        array[i] = users[i];
}

/*

    getUser()

    Gets specified user - TEMPORARY, will have to implement login checks

*/

User getUser(char *username) {
    User users[USER_LIMIT] = { 0 };
    User user = { 0 };

    getAllUsers(users);

    int found = 0;
    for (int i = 0; i < USER_LIMIT && !found; i++) {
        if (!strcmp(users[i].username, username)){
            user = users[i];
            found = 1;
        }
    }

    return user;
}

/*

    setUser()

    Sets user data

*/
int setUser(User user) {
    int flag = 0, existing = 0, lastIndex = -1;
    
    User users[USER_LIMIT] = { 0 };

    getAllUsers(users);

    // Update user in users array
    for (int i = 0; i < USER_LIMIT && !existing; i++) {

        // If username matches, update users array
        if (!strcmp(users[i].username, user.username)){
            users[i] = user;
            existing = 1;
        }

        // Save last index
        if (strlen(users[i].username) > 0)
            lastIndex = i;
    }

    // Append to end of list if not pre-existing user
    if (!existing)
        users[lastIndex + 1] = user;

    FILE *fptr;
    fptr = fopen("users.bin", "wb");

    if (fptr != NULL) {
        fwrite(&users, sizeof(User), USER_LIMIT, fptr);
        flag = 1;
        fclose(fptr);
    }

    return flag;

}