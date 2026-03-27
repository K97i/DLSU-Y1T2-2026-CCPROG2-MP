/*

	species_struct.h
	
	Header file to define the Species struct
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-26-2026
*/

#ifndef SPECIES_STRUCT
#define SPECIES_STRUCT

#define SPECIES_LIMIT 50 // 50 maximum species can be encoded into the database
#define WORD_LIMIT 41 //40 characters + null

typedef struct {
	float height; //Unit of measurement: cm
	float weight; //Unit of measurement: kg
	int sex; // 1 for male and 2 for female (0 is undefined)
	int age;
	char name[WORD_LIMIT]; //includes the Genus and Species
	char biome[WORD_LIMIT];
} Species;

// to save to host database
typedef struct {
	Species species[SPECIES_LIMIT];
	int currentSpeciesCount;
} SpeciesData;

#endif