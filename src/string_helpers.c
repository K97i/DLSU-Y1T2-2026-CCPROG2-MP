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

/*

	@name	flushBuffer();

    @brief	Clears stdin from any extraneous inputs

*/
void flushBuffer() {
    char character;
    // getchar() to receive inputs, starts if and repeats until character is \n or EOF
    while ( ( character = getchar()) != '\n' && character != EOF);
}

/*

	@name	safeStringScanf();

    @brief	Improved Scanf for strings
    @details Improved function to input strings from user. Does not stop at whitespaces, and only stops at newlines. Also flushes buffer

    @param  string          Character pointer (string) to output the data to
    @param  arrayLength     Length of string

*/
int safeStringScanf(char *string, int arrayLength) {
    
    int flag = 0, overflow = 0;

    // EXAMPLE: 31 length == 30 characters consumed, null byte appended to end
    for (int i = 0 ; i < arrayLength && !flag ; i++) {
        char temp;
        scanf("%c", &temp);

        if (temp != '\n' && temp != EOF){
            // terminate string if too long
            if (i == arrayLength - 1){
                overflow = 1;
                string[i] = '\0';
            }
            
            // Stores character to string
            else 
                string[i] = temp;
        }

        // Terminates if it IS \n or EOF
        else {
            string[i] = '\0';
            flag = 1;
        }

    }

    if (!flag){
        flushBuffer();
    }

    return overflow;
}

/*

	@name	safeCharScanf();

    @brief	Improved Scanf for character, flushes buffer after input.

    @param  character   Character pointer to store inputted character to

*/
void safeCharScanf(char *character) {

    // Scans for character
    scanf("%c", character);

    // If \n or EOF, terminate 
    if (*character == '\n' || *character == EOF)
        *character = '\0';

    else
        // Flush stdin
        flushBuffer();

}

/*

	@name	safeIntScanf();

    @brief	Improved Scanf for integer. Checks if valid number and flushes buffer after input.

    @param  number  Integer pointer to store inputted number to

*/
void safeIntScanf(int *number) {
    int valid = 0, temp = 0;

    // While not valid...
    while (!valid) {
        // If scanf input is valid
        if (scanf("%d", &temp) == 1) {
            // Set value to pointer
            *number = temp;
            valid = 1;
        }

        // Retry if invalid
        else {
            printf("Invalid Input!\n");
            printf("\n");
            printf("Re-enter Input: ");
        }

        if (temp != '\n' && temp != EOF)
            // remove any other input (like \n, malformed inputs)
            flushBuffer();
    }
} 

/*

	@name	safeFloatScanf();

    @brief	Improved Scanf for Float. Checks if valid number and flushes buffer after input.

    @param  number  Float pointer to store inputted number to

*/
void safeFloatScanf(float *number) {
    int valid = 0;
    float temp = 0.0;

    // While not valid...
    while (!valid) {
        // If scanf input is valid
        if (scanf("%f", &temp) == 1) {
            // Set value to pointer
            *number = temp;
            valid = 1;
        }

        // Retry if invalid
        else {
            printf("Invalid Input!\n");
            printf("\n");
            printf("Re-enter Input: ");
        }

        if (temp != '\n' && temp != EOF)
            // remove any other input (like \n, malformed inputs)
            flushBuffer();
    }
} 

/*

	@name	menuInputInt();

    @brief	Menu input system using safeIntScanf()

    @param  min     Integer of the minimum number that the menu has 
    @param  max     Integer of the maximum number that the menu has 

*/
int menuInputInt(int min, int max) {
    int input = 0, valid = 0;

    // while invalid...
    while (!valid) {

        printf("Enter selection: ");
        // Get input from user
        safeIntScanf(&input);

        // If less than min / more than min, invalid
        if (input < min || input > max) {
            printf("Invalid selection!\n");
        }

        // else, exit loop
        else {
            valid = 1;
        }

    }

    return input;
}


/*

	@name	checkIfBanned();

    @brief	Menu input system using safeIntScanf()

    @param  input           Character pointer (string) of the input string 
    @param  wordLength      Length of the input string 

*/
int checkIfBanned(char *input, int wordLength) {
    char bannedWords[BANNED_WORDS_LIST][BANNED_WORDS_LENGTH] = {
        "[EXIT]", "\t"
    };
    int flag = 0;

    // for each banned word...
    for (int i = 0 ; i < BANNED_WORDS_LIST && !flag ; i++) {
        // for each substring...
        for (int j = 0 ; j < strlen(input) - strlen(bannedWords[i] - 1) && !flag ; j++) {
            // if substring matches banned word...
            if (!strncmp(input + j, bannedWords[i], strlen(bannedWords[i]))) {
                // mark as invalid
                flag = 1;
            }
        }
    }

    return flag;
}