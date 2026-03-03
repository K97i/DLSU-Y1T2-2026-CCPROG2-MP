/*

    encryption.c

    Contains the main XOR encryption function

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-3-2026

*/

#include <stdio.h>
#include <string.h>

void encrypt(char *plaintext, char *username, char *key, char *output) {

    // Encrypt with Username

    for (int i = 0; i < (int) strlen(plaintext); i++) {
        output[i] = plaintext[i] ^ username[i % (int) strlen(username)]; 
    }

    // Encrypt with encryption key

    for (int i = 0; i < (int) strlen(output); i++) {
        output[i] = output[i] ^ key[i % (int) strlen(key)]; 
    }
}

void decrypt(char *ciphertext, char *username, char *key, char *output) {

    // Decrypt with encryption key

    for (int i = 0; i < (int) strlen(ciphertext); i++) {
        output[i] = ciphertext[i] ^ key[i % (int) strlen(key)]; 
    }

    // Decrypt with Username

    for (int i = 0; i < (int) strlen(output); i++) {
        output[i] = output[i] ^ username[i % (int) strlen(username)]; 
    }
}