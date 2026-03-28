#ifndef DISPLAY_HELPERS
#define DISPLAY_HELPERS

#include "user_struct.h"
#include "species_struct.h"

void printSpecies(Species *species, int numbered);
void printSpeciesData(SpeciesData *species, int numbered);
void printSpeciesDatabaseInfo(SpeciesData *species);
void printSpeciesSpecialInfo(Species *species, SDB *sDB, int databaseIndex);

#endif