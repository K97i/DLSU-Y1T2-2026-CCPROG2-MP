/*

    string_helpers.c

    Functions to help with I/O of strings

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-7-2026

*/

#include <stdio.h>
#include <string.h>

#define BANNED_WORDS_LIST 2
#define BANNED_WORDS_LENGTH 10

void flushBuffer() {
    char character;
    while ( ( character = getchar()) != '\n' && character != EOF);
}

int safeStringScanf(char *string, int arrayLength) {
    
    int flag = 0, overflow = 0;
    char buffer; // if stdin is not empty after the for loop

    // EXAMPLE: 31 length == 30 characters consumed, null byte appended to end
    for (int i = 0 ; i < arrayLength && !flag ; i++) {
        char temp;
        scanf("%c", &temp);

        if (temp != '\n' && temp != EOF){
            // terminate string if too long
            if (i == arrayLength - 1)
                string[i] = '\0';
            
            else 
                string[i] = temp;
        }

        else {
            string[i] = '\0';
            flag = 1;
        }

    }

    if (!flag && ( buffer = getchar() ) != '\n' && buffer != EOF){
        overflow = 1;
        flushBuffer();
    }

    return overflow;
}

void safeCharScanf(char *character) {

    scanf("%c", character);

    if (*character == '\n')
        *character = '\0';

    flushBuffer();

}

void safeIntScanf(int *number) {
    int valid = 0, temp = 0;

    while (!valid) {
        if (scanf("%d", &temp) == 1) {
            *number = temp;
            valid = 1;
        }

        else {
            printf("Invalid Input!\n");
        }
    }

    // remove any other input (like \n, malformed inputs)
    flushBuffer();
} 

void safeFloatScanf(float *number) {
    int valid = 0;
    float temp = 0.0;

    while (!valid) {
        if (scanf("%f", &temp) == 1) {
            *number = temp;
            valid = 1;
        }

        else {
            printf("Invalid Input!\n");
        }
    }

    // remove any other input (like \n, malformed inputs)
    flushBuffer();
} 

int menuInputInt(int min, int max) {
    int input = 0, valid = 0;

    // while invalid...
    while (!valid) {
        printf("Enter selection: ");
        safeIntScanf(&input);

        if (input < min || input > max) {
            printf("Invalid selection!\n");
        }

        else {
            valid = 1;
        }
    }

    return input;
}


int checkIfBanned(char input[], int wordLength) {
    char bannedWords[BANNED_WORDS_LIST][BANNED_WORDS_LENGTH] = {
        "[EXIT]", " , "
    };
    int flag = 0;

    // for each banned word...
    for (int i = 0 ; i < BANNED_WORDS_LIST && !flag ; i++) {
        // for each substring...
        for (int j = 0 ; j < strlen(input) - strlen(bannedWords[i] - 1) && !flag ; j++) {
            // if substring matches banned word...
            if (!strncmp(input + j, bannedWords[i], strlen(bannedWords[i]))) {
                flag = 1;
            }
        }
    }

    return flag;
}