#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "config_struct.h"
#include "string_helpers.h"
#include "file_operation.h"
#include "search_and_sort.h"

void resetConfig(Config *config) {
    Config configDefaults;

    strcpy(configDefaults.administratorKey, "OVERRIDE-1234");
    strcpy(configDefaults.encryptionKey, "N0T-@3S-3NCRYPT10N");

    *config = configDefaults;
    setConfig(*config);
}

void resetSpeciesToPokemon() {

    // All data / lore pulled from https://bulbapedia.bulbagarden.net
    SDB sDB = { 0 };

    // Greninja
    strcpy(sDB.species[0].name, "Greninja");
    strcpy(sDB.species[0].biome, "Kalos");
    strcpy(sDB.species[0].description, "The Ninja Pokemon. It creates throwing stars out of compressed water. When it spins them and throws them at high speed, these stars can split metal in two.");
    sDB.species[0].conservationStatus = 2;

    // Rowlet
    strcpy(sDB.species[1].name, "Rowlet");
    strcpy(sDB.species[1].biome, "Alola");
    strcpy(sDB.species[1].description, "The Grass Quill Pokemon. This wary Pokémon uses photosynthesis to store up energy during the day, while becoming active at night.");
    sDB.species[1].conservationStatus = 2;

    // Mudkip
    strcpy(sDB.species[2].name, "Mudkip");
    strcpy(sDB.species[2].biome, "Hoenn");
    strcpy(sDB.species[2].description, "On land, it can powerfully lift large boulders by planting its four feet and heaving. It sleeps by burying itself in soil at the water's edge.");
    sDB.species[2].conservationStatus = 1;

    // Cyndaquil
    strcpy(sDB.species[3].name, "Cyndaquil");
    strcpy(sDB.species[3].biome, "Johto");
    strcpy(sDB.species[3].description, "The Fire Mouse Pokemon. It is timid, and always curls itself up in a ball. If attacked, it flares up its back for protection.");
    sDB.species[3].conservationStatus = 1;

    // Cyndaquil
    strcpy(sDB.species[4].name, "Togepi");
    strcpy(sDB.species[4].biome, "Johto");
    strcpy(sDB.species[4].description, "The Spike Ball Pokemon. The shell seems to be filled with joy. It is said that it will share good luck when treated kindly.");
    sDB.species[4].conservationStatus = 1;

    sDB.currentSpeciesCount = 5;

    SpeciesDataBaseSort(&sDB);
    setSpecies(&sDB);
}

void resetUserData(UserData *userData) {
    UserData clean = { 0 };
    *userData = clean;
    setUsers(userData);
}

void resetDatabases(UserData *userData, Config *config) {
    char overrideTemp[CONFIG_STRING_LEN] = "";
    int firstConfirmation = 0, secondConfirmation = 0, overrideFlag = 0,
        exitFlag = 0, select = 0;

    while (!firstConfirmation && !exitFlag) {
        printf("Reset everything to its defaults?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        select = menuInputInt(1, 2);

        switch (select) {
            case 1: 
                firstConfirmation = 1;
                break;

            case 2: 
                exitFlag = 1;
                break;
        }
    }

    while (!secondConfirmation && !exitFlag) {
        printf("Last warning! This will reset User data, Species Data, and Config files! Confirm?\n");
        printf("[1] Confirm\n");
        printf("[2] Cancel\n");
        select = menuInputInt(1, 2);

        switch (select) {
            case 1: 
                secondConfirmation = 1;
                break;

            case 2: 
                exitFlag = 1;
                break;
        }
    }

    while (!overrideFlag && !exitFlag) {
        printf("Enter override key to reset: ");
        
        safeStringScanf(overrideTemp, CONFIG_STRING_LEN);

        if (!strcmp("[EXIT]", overrideTemp))
            exitFlag = 1;

        else if (!strcmp(overrideTemp, config->administratorKey))
            overrideFlag = 1;

        else {
            printf("Invalid override key! Database Reset cancelled.\n");
            exitFlag = 1;
        }
    }

    if (firstConfirmation && secondConfirmation && overrideFlag && !exitFlag) {
        resetUserData(userData);
        resetSpeciesToPokemon();
        resetConfig(config);
    }

}