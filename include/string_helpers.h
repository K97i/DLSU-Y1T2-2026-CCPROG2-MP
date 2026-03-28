/*

    string_helpers.h

    Header file for string_helpers.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-7-2026

*/

#ifndef STRING_HELPERS
#define STRING_HELPERS

void flushBuffer();
int safeStringScanf(char *string, int arrayLength);
void safeCharScanf(char *character);
int menuInputInt(int min, int max);
int checkIfBanned(char input[], int wordLength);

#endif