/*

    test_suite.c

    Contains tester functions for file_operations.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 3-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"
#include "user_struct.h"
#include "file_operation.h"
#include "encryption.h"
#include "string_helpers.h"
#include "reset_databases.h"

/*

	@name	configTest();

    @brief	Tests Config database file operations

*/
void configTest() {

    // Test reading and writing config
    
    printf("=== [ CONFIG READ / WRITE TEST ] ===\n\n");

    Config configTest, configRead;

    strcpy(configTest.administratorKey, "Hi!");
    strcpy(configTest.encryptionKey, "Hello!");

    // Sets config
    setConfig(configTest);

    configRead = getConfig();

    printf("Saved Override Key: %s\n", configRead.administratorKey);
    printf("Saved Encryption Key: %s\n", configRead.encryptionKey);

    // Test resetting config

    printf("\n");

    printf(" === [ CONFIG DEFAULTS TESTING ] ===\n\n");

    resetConfig(&configRead);

    printf("Default Override Key: %s\n", configRead.administratorKey);
    printf("Default Encryption Key: %s\n", configRead.encryptionKey);

    printf("\n");
}

/*

	@name	encryptionTest();

    @brief	Tests XOR encryption

*/
void encryptionTest() {

    Config config = getConfig();
    char string[10] = "Hello";
    char output1[10] = "", output2[10] = "";
    printf("=== [ ENCRYPT / DECRYPT TEST ] ===\n\n");

    // Encrypt

    printf(" === [ ENCRYPTION TEST ] ===\n\n");

    printf("Plaintext: %s\n", string);
    printf("Encryption Key: %s\n", config.encryptionKey);

    encrypt(string, &config, output1);
    
    printf("Output of encryption: %s\n\n", output1);

    // Decrypt

    printf(" === [ DECRYPTION TEST ] ===\n\n");

    printf("Ciphertext: %s\n", output1);

    encrypt(output1, &config, output2);

    printf("Output of decryption: %s\n\n", output2);

}

/*

	@name	userTests();

    @brief	Tests User database file operations

*/
void userTests() {
    UserData users = { 0 };
    User user = { 0 };

    strcpy(user.username, "Markiplier");
    strcpy(user.password, "MARK2702");
    user.administrator = 0;

    printf("=== [ USER TEST ] ===\n\n");

    // Save user

    printf("=== [ Initial Variables ] ===\n\n");

    printf("Username: %s\n", user.username);
    printf("Password: %s\n", user.password);
    printf("Admin: %d\n\n", user.administrator);

    users.users[users.currentUserCount] = user;
    users.currentUserCount++;
    setUsers(&users);

    // Get users

    UserData received = { 0 };
    getUsers(&received);

    for (int i = 0 ; i < received.currentUserCount ; i++) {
        User saved = received.users[i];
        printf("=== [ Saved Variables ] ===\n\n");

        printf("Username: %s\n", saved.username);
        printf("Password: %s\n", saved.password);
        printf("Admin: %d\n\n", saved.administrator);
    }

}

/*

	@name	inputTests();

    @brief	Tests safeScanf functions

*/
void inputTests() {
    printf("=== [ INPUT TEST ] ===\n\n");

    // Tests character input
    char character;
    printf("Input a character: ");
    safeCharScanf(&character);

    printf("Received: %c\n", character);

    // Tests string input
    char hello[10] = { 0 };
    printf("Input a string: ");
    int check = safeStringScanf(hello, 10);

    if (check) {
        printf("WARNING! String overflowed, cut off at last character\n");
    }

    printf("Received: %s\n", hello);

    // Tests menu system
    menuInputInt(1,3);
}

/*

	@name	testSuite();

    @brief	Full test suite, runs all functions

*/
void testSuite() {
    
    printf("=== [ TEST SUITE ] ===\n");

    configTest();
    encryptionTest();
    userTests();
    inputTests();

    printf("\n\n");
}