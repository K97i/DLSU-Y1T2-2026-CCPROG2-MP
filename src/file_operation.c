/*

    file_operations.c

    Contains all file operations done by the program.
    Specifically get-set operations for the config file, user database, and species database.

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"
#include "user_struct.h"

/*

    Getters-setters idea based from my own project (Crydengo, written in JS), wherein it looks configs up from a DB (SQLite) - Elo
    https://github.com/K97i/crydengo/blob/main/src/helpers/guild-config.js

*/

/*

	@name	getConfig();

    @brief	Gets the config from config.bin and returns the config struct

    @param	plaintext   Input string
    @param	config      Pointer to the configuration struct (where the encryption key lies)
    @param	output	    Output string

    @return result of read operation, returns the saved config file
*/
Config getConfig() {
    Config configRead = { 0 };

    FILE *fptr;
    fptr = fopen("config.txt", "r");

    if (fptr != NULL) {
        fscanf(fptr, "%[^\t]\t%[^\n]", configRead.administratorKey, configRead.encryptionKey);
        fclose(fptr);
    }


    return configRead;
}

/*

	@name	setConfig();

    @brief	Saves the inputted config to config.txt

    @param	configWrite   New config to be written

    @return Boolean if write is successful, 1 if success, 0 if fail
*/
int setConfig(const Config configWrite) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("config.txt", "w");

    if (fptr != NULL) {
        fprintf(fptr, "%s\t%s", configWrite.administratorKey, configWrite.encryptionKey);
        fclose(fptr);
        flag = 1;
    }

    return flag;
}

/*

	@name	getUsers();

    @brief	Gets the user database from users.txt

    @param	userData   Pointer to the userData variable to be written

*/
void getUsers(UserData *userData) {
    FILE *fptr;
    fptr = fopen("users.txt", "r");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        // Get number of users
        fscanf(fptr, "%d\n", &userData->currentUserCount);

        // Loop through every user
        for (int i = 0 ; i < userData->currentUserCount ; i++) {
            // Get user data
            fscanf(fptr, "%[^\t]%*c%[^\t]%*c%d\t%d\n", userData->users[i].username, 
                                                userData->users[i].password,
                                                &userData->users[i].administrator,
                                                &userData->users[i].currentSpeciesCount);

            // Get pokedex data, for each pokedex entry
            for (int j = 0 ; j < userData->users[i].currentSpeciesCount ; j++) {
                fscanf(fptr, "%[^\t]\t%f\t%f\t%d\t%d\n",   userData->users[i].species[j].name,
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

	@name	setUsers();

    @brief	Sets the user database to users.txt

    @param	userData   Pointer to the userData variable to be read from

*/
int setUsers(const UserData *userData) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("users.txt", "w");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        // Save user count
        fprintf(fptr, "%d\n", userData->currentUserCount);

        // Save each user
        for (int i = 0 ; i < userData->currentUserCount ; i++) {
            // Save user metadata
            fprintf(fptr, "%s\t%s\t%d\t%d\n",    userData->users[i].username, 
                                                    userData->users[i].password,
                                                    userData->users[i].administrator,
                                                    userData->users[i].currentSpeciesCount);

            // Save user's pokedex data
            for (int j = 0 ; j < userData->users[i].currentSpeciesCount ; j++) {
                fprintf(fptr, "%s\t%f\t%f\t%d\t%d\n",  userData->users[i].species[j].name,
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

	@name	getSpecies();

    @brief	Gets the species database from species.txt

    @param	sDB     Pointer to the SpeciesDatabase variable to be written

*/
void getSpecies(SDB *sDB) {
    FILE *fptr;
    fptr = fopen("species.txt", "r");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        // Get number of species
        fscanf(fptr, "%d", &sDB->currentSpeciesCount);

        // For each species...
        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            // Get metadata of species
            fscanf(fptr, " %[^\t]\t%[^\t]\t%d\t%d\t%[^\n]", sDB->species[i].name, 
                                                    sDB->species[i].biome,
                                                    &sDB->species[i].conservationStatus,
                                                    &sDB->species[i].userInputCount,
                                                    sDB->species[i].description);
        }

        fclose(fptr);

    }

}

/*

	@name	setSpecies();

    @brief	Sets the species database to species.txt

    @param	sDB     Pointer to the species database variable to be read from

*/
int setSpecies(SDB *sDB) {
    int flag = 0;

    FILE *fptr;
    fptr = fopen("species.txt", "w");

    if (fptr != NULL) {
        fseek(fptr, 0, SEEK_SET);
        // Save species count
        fprintf(fptr, "%d\n", sDB->currentSpeciesCount);

        // For each species...
        for (int i = 0 ; i < sDB->currentSpeciesCount ; i++) {
            // Save species metadata
            fprintf(fptr, "%s\t%s\t%d\t%d\t%s\n", sDB->species[i].name, 
                                                    sDB->species[i].biome,
                                                    sDB->species[i].conservationStatus,
                                                    sDB->species[i].userInputCount,
                                                    sDB->species[i].description);
        }

        flag = 1;
        fclose(fptr);
    }

    return flag;
}
