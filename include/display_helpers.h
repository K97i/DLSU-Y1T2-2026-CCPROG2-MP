#ifndef DISPLAY_HELPERS
#define DISPLAY_HELPERS

#include "user_struct.h"
#include "species_struct.h"

void printSpecies(Species *species, int numbered, int customNumber);
void printSpeciesInfo(Species *species, SDB *sDB, int databaseIndex);

#endif