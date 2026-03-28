/*

    encryption.c

    Contains the main XOR encryption function

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"

void encrypt(char *plaintext, Config *config, char *output) {

    // Encrypt with encryption key

    for (int i = 0; i < (int) strlen(plaintext); i++) {
        output[i] = plaintext[i] ^ config->encryptionKey[i % (int) strlen(config->encryptionKey)]; 
    }

}

void decrypt(char *ciphertext, Config *config, char *output) {

    // Decrypt with encryption key

    for (int i = 0; i < (int) strlen(ciphertext); i++) {
        output[i] = ciphertext[i] ^ config->encryptionKey[i % (int) strlen(config->encryptionKey)]; 
    }

}