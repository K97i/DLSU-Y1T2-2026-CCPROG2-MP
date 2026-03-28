/*

    file_operations.c

    Contains all file operations done by the program.
    Specifically get-set operations for the config file, user database, and species database.

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

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
    fptr = fopen("config.txt", "r");

    if (fptr != NULL) {
        fscanf(fptr, "%s , %s", configRead.administratorKey, configRead.encryptionKey);
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
    fptr = fopen("config.txt", "w");

    if (fptr != NULL) {
        fprintf(fptr, "%s , %s", configWrite.administratorKey, configWrite.encryptionKey);
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

    getUsers()

    Gets users from DB

*/

void getUsers(UserData *userData) {
    FILE *fptr;
    fptr = fopen("users.txt", "r");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        fscanf(fptr, "%d", &userData->currentUserCount);

        for (int i = 0 ; i < userData->currentUserCount ; i++) {
            fscanf(fptr, "%s , %s , %d , %d", userData->users[i].username, 
                                                userData->users[i].password,
                                                &userData->users[i].administrator,
                                                &userData->users[i].currentSpeciesCount);

            for (int j = 0 ; j < userData->users[i].currentSpeciesCount ; j++) {
                fscanf(fptr, "%s , %f , %f , %d , %d",   userData->users[i].species[j].name,
                                                                &userData->users[i].species[j].height,
                                                                &userData->users[i].species[j].weight,
                                                                &userData->users[i].species[j].sex,
                                                                &userData->users[i].species[j].age);
            }
        }

        fclose(fptr);
    }

}

/*

    setUsers()

    Sets user data

*/
int setUsers(const UserData *userData) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("users.txt", "w");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        fprintf(fptr, "%d\n", userData->currentUserCount);

        for (int i = 0 ; i < userData->currentUserCount ; i++) {
            fprintf(fptr, "%s , %s , %d , %d\n",    userData->users[i].username, 
                                                    userData->users[i].password,
                                                    userData->users[i].administrator,
                                                    userData->users[i].currentSpeciesCount);

            for (int j = 0 ; j < userData->users[i].currentSpeciesCount ; j++) {
                fprintf(fptr, "%s , %f , %f , %d , %d\n",  userData->users[i].species[j].name,
                                                                userData->users[i].species[j].height,
                                                                userData->users[i].species[j].weight,
                                                                userData->users[i].species[j].sex,
                                                                userData->users[i].species[j].age);
            }
        }

        flag = 1;
        fclose(fptr);
    }

    return flag;
}

/*

    getSpecies()

    Sets species data

*/
void getSpecies(SDB *sDB) {
    FILE *fptr;
    fptr = fopen("species.txt", "r");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        fscanf(fptr, "%d", &sDB->currentSpeciesCount);

        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            fscanf(fptr, "%s , %s , %d", sDB->species[i].name, 
                                                sDB->species[i].biome,
                                                &sDB->species[i].userInputCount);
        }

        fclose(fptr);
    }

}

int setSpecies(SDB *sDB) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("species.txt", "w");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        fprintf(fptr, "%d\n", sDB->currentSpeciesCount);

        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            fprintf(fptr, "%s , %s , %d , %s", sDB->species[i].name, 
                                                sDB->species[i].biome,
                                                sDB->species[i].userInputCount,
                                                sDB->species[i].description);
        }

        flag = 1;
        fclose(fptr);
    }

    return flag;
}
