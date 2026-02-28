/*

    test_suite.c

    Contains tester functions for file_operations.c

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#include <stdio.h>
#include <string.h>

#include "config_struct.h"
#include "file_operation.h"

/*

    configTest()

    Tests Read / Write operations, config reset, etc.

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