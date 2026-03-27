/*

    encryption.c

    Contains the main XOR encryption function

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#include <string.h>

#include "config_struct.h"

void encrypt(char *plaintext, char *username, Config *config, char *output) {

    // Encrypt with Username

    for (int i = 0; i < (int) strlen(plaintext); i++) {
        output[i] = plaintext[i] ^ username[i % (int) strlen(username)]; 
    }

    // Encrypt with encryption key

    for (int i = 0; i < (int) strlen(output); i++) {
        output[i] = output[i] ^ config->encryptionKey[i % (int) strlen(config->encryptionKey)]; 
    }
}

void decrypt(char *ciphertext, char *username, Config *config, char *output) {

    // Decrypt with encryption key

    for (int i = 0; i < (int) strlen(ciphertext); i++) {
        output[i] = ciphertext[i] ^ config->encryptionKey[i % (int) strlen(config->encryptionKey)]; 
    }

    // Decrypt with Username

    for (int i = 0; i < (int) strlen(output); i++) {
        output[i] = output[i] ^ username[i % (int) strlen(username)]; 
    }
}