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

    scanf("%d", number);

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