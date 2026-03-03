/*

    encryption.h

    Header file for encryption.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-3-2026

*/

#ifndef ENCRYPTION_FUNCTIONS
#define ENCRYPTION_FUNCTIONS

void encrypt(char *plaintext, char *username, char *key, char *output);
void decrypt(char *ciphertext, char *username, char *key, char *output);

#endif