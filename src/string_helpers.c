/*

    string_helpers.c

    Functions to help with I/O of strings

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-7-2026

*/

#include <stdio.h>
#include <string.h>

void flush_buffer() {
    char character;
    while ( ( character = getchar()) != '\n' && character != EOF);
}

void safe_string_scanf(char *string, int length) {
    
    int flag = 0;
    char buffer; // if stdin is not empty after the for loop

    // EXAMPLE: 31 length == 30 characters consumed, null byte appended to end
    for (int i = 0 ; i < length - 1 && !flag ; i++) {
        char temp;
        scanf("%c", &temp);

        if (temp == '\n' || temp == EOF) {
            string[i] = '\0';
            flag = 1;
        }

        else {
            string[i] = temp;
            i++;
        }
    }

    // explicit null termination in case of more than target length
    string[length - 1] = '\0';

    if (!flag && ( buffer = getchar()) != '\n' && buffer != EOF)
        flush_buffer();

}

char safe_char_scanf(char *character) {

    scanf("%c", character);

    flush_buffer();

    return *character;

}