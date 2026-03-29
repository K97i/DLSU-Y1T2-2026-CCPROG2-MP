#include <stdio.h>
#include <string.h>

#include "user_struct.h"
#include "species_struct.h"
#include "config_struct.h"
#include "encryption.h"
#include "string_helpers.h"
#include "file_operation.h"
#include "search_and_sort.h"

/*

    @name   resetConfig();

    @brief  Resets the config to its defaults

    @param  *config Pointer to the program configuration data

*/
void resetConfig(Config *config) {
    Config configDefaults;

    strcpy(configDefaults.administratorKey, "OVERRIDE-1234");
    strcpy(configDefaults.encryptionKey, "N0T-@3S-3NCRYPT10N");

    *config = configDefaults;
    setConfig(*config);
}

/*

    @name   resetSpeciesToRealSpecies();

    @brief  Fills the SpeciesDataBase with predefined real species


*/
void resetSpeciesToRealSpecies() {

    SDB sDB = { 0 };

    /*
        Gray Wolf (Canis lupus)

        Data sourced from:
        https://nationalzoo.si.edu/animals/gray-wolf
        https://www.sciencedirect.com/topics/agricultural-and-biological-sciences/canis-lupus
    */
    strcpy(sDB.species[0].name, "Canis lupus");
    strcpy(sDB.species[0].biome, "Forest");
    strcpy(sDB.species[0].description, "Canis lupus is commonly known as the wolf, from which the domestic dog, Canis lupus familiaris, is descended. It exhibits social structures that include dominance relationships within its social unit.");
    sDB.species[0].conservationStatus = 2;

    /*
        Bobcat (Lynx rufus)

        Data sourced from:
        https://nationalzoo.si.edu/animals/bobcat
    */
    strcpy(sDB.species[1].name, "Lynx rufus");
    strcpy(sDB.species[1].biome, "Forest");
    strcpy(sDB.species[1].description, "Lynx rufus, commonly known as the bobcat, are often confused with the other three \"lynx\" species, the Canadian lynx, Iberian lynx and Eurasian lynx. Bobcats are slightly smaller than other lynx and live in warmer climates at lower latitudes.");
    sDB.species[1].conservationStatus = 2;

    /*
        Tawny Owl (Strix aluco)

        Data sourced from:
        https://ebird.org/species/tawowl1
        https://datazone.birdlife.org/species/factsheet/tawny-owl-strix-aluco
    */
    strcpy(sDB.species[2].name, "Strix aluco");
    strcpy(sDB.species[2].biome, "Forest");
    strcpy(sDB.species[2].description, "Strix aluco, commonly known as the tawny owl, are medium-sized owls with deep black eyes, strictly nocturnal and infrequently seen.");
    sDB.species[2].conservationStatus = 2;

    /*
        Common snapping turtle (Chelydra serpentina)

        Data sourced from:
        https://animaldiversity.org/accounts/Chelydra_serpentina/
        https://ontarionature.org/programs/community-science/reptile-amphibian-atlas/snapping-turtle/
    */
    strcpy(sDB.species[3].name, "Chelydra serpentina");
    strcpy(sDB.species[3].biome, "Swamps");
    strcpy(sDB.species[3].description, "Chelydra serpentina, commonly known as the common snapping turtle, normally has a shell length ranging from 8 -18 1/2\" and has a tail nearly as long as the shell.");
    sDB.species[3].conservationStatus = 2;

    /*
        Koala (Phascolarctos cinereus)

        Data sourced from:
        https://animaldiversity.org/accounts/Chelydra_serpentina/
        https://ontarionature.org/programs/community-science/reptile-amphibian-atlas/snapping-turtle/
    */
    strcpy(sDB.species[4].name, "Phascolarctos cinereus");
    strcpy(sDB.species[4].biome, "Forest");
    strcpy(sDB.species[4].description, "Phascolarctos cinereus is more commonly known as the koala. Virtually tailless, koala bodies are stout and gray, with a pale yellow or cream-coloured chest and mottling on the rump.");
    sDB.species[4].conservationStatus = 1;

    sDB.currentSpeciesCount = 5;

    SpeciesDataBaseSort(&sDB); //Sorts the inputs
    setSpecies(&sDB); //Writes it into the text file
}

/*

    @name   resetSpeciesToPokemon();

    @brief  Fills the SpeciesDataBase with predefined Pokemons


*/
void resetSpeciesToPokemon() {

    // All data / lore pulled from https://bulbapedia.bulbagarden.net
    SDB sDB = { 0 };

    //Fills the species database 
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

    // Togepi
    strcpy(sDB.species[4].name, "Togepi");
    strcpy(sDB.species[4].biome, "Johto");
    strcpy(sDB.species[4].description, "The Spike Ball Pokemon. The shell seems to be filled with joy. It is said that it will share good luck when treated kindly.");
    sDB.species[4].conservationStatus = 1;

    sDB.currentSpeciesCount = 5;

    SpeciesDataBaseSort(&sDB); //Sorts the inputs
    setSpecies(&sDB); //Writes it into the text file
}

/*

    @name   resetUserConfig();

    @brief  Resets UserData to default

    @param  *userData   Pointer to the array of users used globally
    @param  *userData   Pointer to the configuration struct

*/
void resetUserData(UserData *userData, Config *config) {
    UserData clean = { 0 };
    User new = { 0 }, reg = { 0 };

    // Admin user
    strcpy(new.username, "admin");
    encrypt("Charmander!", config, new.password);
    new.administrator = 1;

    // Reg user
    strcpy(reg.username, "test");
    encrypt("notAdmin", config, reg.password);

    // Set users to clean
    clean.users[0] = new;
    clean.users[1] = reg;
    clean.currentUserCount = 2;

    // Sort and save
    UserSort(&clean);
    *userData = clean;
    setUsers(userData);
}

/*

    @name   resetDatabases();

    @brief  Main function that resets the user and species database as well as the config

    @param  *userData   Pointer to the array of users used globally
    @param  *config     Pointer to the program configuration data

*/
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
        
        safeStringScanf(overrideTemp, CONFIG_STRING_LEN); //gets the user's input and clears the input stream

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
        resetConfig(config);
        resetUserData(userData, config);
        //resetSpeciesToPokemon();
        resetSpeciesToRealSpecies();
    }

}