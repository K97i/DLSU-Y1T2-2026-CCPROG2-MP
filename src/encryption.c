/*

    encryption.c

    Contains the main XOR encryption function

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-27-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"

/*

	@name	encrypt();

    @brief	Encrypts the data given

    @param	plaintext   Input string
    @param	config      Pointer to the configuration struct (where the encryption key lies)
    @param	output	    Output string

*/
void encrypt(char *plaintext, Config *config, char *output) {

    // Encrypt with encryption key
    // For the length of the input string...
    for (int i = 0; i < (int) strlen(plaintext); i++) {
        // ^ => XOR operator
        // "i % (int) strlen(config->encryptionKey)" => Loops if encryptionKey ends before input string
        output[i] = plaintext[i] ^ config->encryptionKey[i % (int) strlen(config->encryptionKey)]; 
    }

}
