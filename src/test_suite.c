/*

    test_suite.c

    Contains tester functions for file_operations.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"
#include "user_struct.h"
#include "file_operation.h"
#include "encryption.h"

/*

    configTest()

    Tests Config read / writes, etc.

*/
void configTest() {

    // Test reading and writing config
    
    printf("=== [ CONFIG READ / WRITE TEST ] ===\n\n");

    Config configTest, configRead;

    strcpy(configTest.administratorKey, "Hi!");
    strcpy(configTest.encryptionKey, "Hello!");

    setConfig(configTest);

    configRead = getConfig();

    printf("Saved Override Key: %s\n", configRead.administratorKey);
    printf("Saved Encryption Key: %s\n", configRead.encryptionKey);

    // Test resetting config

    printf("\n");

    printf(" === [ CONFIG DEFAULTS TESTING ] ===\n\n");

    resetConfig();

    configRead = getConfig();

    printf("Default Override Key: %s\n", configRead.administratorKey);
    printf("Default Encryption Key: %s\n", configRead.encryptionKey);

    printf("\n");
}

/*

    encryptionTest()

    Tests XOR encryption / decryption functions

*/
void encryptionTest() {

    Config config = getConfig();
    char string[10] = "Hello";
    char username[10] = "MERK";
    char output1[10] = "", output2[10] = "";
    printf("=== [ ENCRYPT / DECRYPT TEST ] ===\n\n");

    // Encrypt

    printf(" === [ ENCRYPTION TEST ] ===\n\n");

    printf("Plaintext: %s\n", string);
    printf("Username: %s\n", username);
    printf("Encryption Key: %s\n", config.encryptionKey);

    encrypt(string, username, config.encryptionKey, output1);
    
    printf("Output of encryption: %s\n", output1);

    // Decrypt

    printf(" === [ DECRYPTION TEST ] ===\n\n");

    printf("Ciphertext: %s\n", output1);

    decrypt(output1, username, config.encryptionKey, output2);

    printf("Output of decryption: %s\n", output2);

}

void userTests() {
    User user = { 0 };

    strcpy(user.username, "Markiplier");
    strcpy(user.password, "MARK2702");
    user.administrator = 0;

    printf("=== [ USER TEST ] ===\n\n");

    // Save user

    printf("=== [ Initial Variables ] ===\n\n");

    printf("Username: %s\n", user.username);
    printf("Password: %s\n", user.password);
    printf("Admin: %d\n", user.administrator);

    setUser(user);

    // Get user

    User saved = getUser("Markiplier");

    printf("=== [ Saved Variables ] ===\n\n");

    printf("Username: %s\n", saved.username);
    printf("Password: %s\n", saved.password);
    printf("Admin: %d\n", saved.administrator);

    // Multiple User Tests

    printf("=== [ MULTIPLE USERS TEST ] ===\n\n");

    User user1 = { 0 };

    strcpy(user1.username, "JohnDoe");
    strcpy(user1.password, "yespapa");
    user1.administrator = 0;

    User user2 = { 0 };

    strcpy(user2.username, "JaneDoe");
    strcpy(user2.password, "nopapa");
    user2.administrator = 0;

    User user3 = { 0 };

    strcpy(user3.username, "Steve");
    strcpy(user3.password, "dododo");
    user3.administrator = 1;

    setUser(user1);
    setUser(user2);
    setUser(user3);

    User saved1 = getUser("JohnDoe");

    printf("=== [ USER 1 ] ===\n\n");

    printf("Username: %s\n", saved1.username);
    printf("Password: %s\n", saved1.password);
    printf("Admin: %d\n", saved1.administrator);

    User saved2 = getUser("JaneDoe");

    printf("=== [ USER 2 ] ===\n\n");

    printf("Username: %s\n", saved2.username);
    printf("Password: %s\n", saved2.password);
    printf("Admin: %d\n", saved2.administrator);

    User saved3 = getUser("Steve");

    printf("=== [ USER 3 ] ===\n\n");

    printf("Username: %s\n", saved3.username);
    printf("Password: %s\n", saved3.password);
    printf("Admin: %d\n", saved3.administrator);

}
