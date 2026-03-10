/*

	species_struct.h
	
	Header file to define the Species struct
	
	Author: SACRAMENTO, Yvan Gregorio A.
	Last Modified: 3-10-2026
*/

#define SPECIES_LIMIT 1000 //1000 maximum species can be encoded into the database
#define WORD_LIMIT 41 //40 characters + null


typedef struct {
	char name[WORD_LIMIT]; //includes the Genus and Species
	char biome[WORD_LIMIT];
	float height; //Unit of measurement: cm
	float weight; //Unit of measurement: kg
	int sex; // 1 for male and 2 for female (0 is undefined)
	int age;
} Species;