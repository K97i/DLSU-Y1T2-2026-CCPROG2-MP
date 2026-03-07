/*

    string_helpers.c

    Functions to help with I/O of strings

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-7-2026

*/

#include <stdio.h>
#include <string.h>

void flushBuffer() {
    char character;
    while ( ( character = getchar()) != '\n' && character != EOF);
}

int safeStringScanf(char *string, int arrayLength) {
    
    int flag = 0, overflow = 0;
    char buffer; // if stdin is not empty after the for loop

    // EXAMPLE: 31 length == 30 characters consumed, null byte appended to end
    for (int i = 0 ; i < arrayLength - 1 && !flag ; i++) {
        char temp;
        scanf("%c", &temp);

        if (temp != '\n' && temp != EOF)
            string[i] = temp;

        else {
            string[i] = '\0';
            flag = 1;
        }
    }

    // explicit null termination in case of more than target length
    string[arrayLength - 1] = '\0';

    if (!flag && ( buffer = getchar()) != '\n' && buffer != EOF){
        overflow = 1;
        flushBuffer();
    }

    return overflow;
}

char safeCharScanf(char *character) {

    scanf("%c", character);

    if (*character == '\n')
        *character = '\0';

    // redundant if check for \n, but to keep consistent with surrounding code
    else if (*character != '\n' && *character != EOF)
        flushBuffer();

    return *character;

}