#include <stdio.h>

#include "test_suite.h"
#include "string_helpers.h"
#include "logo.h"

/*
    There are 2 hard problems in computer science: cache invalidation, naming things, and off-by-1 errors.
    - Leon Bambrick
*/

void firstMenu() {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("[1] Login\n");
        printf("[2] Register\n");
        printf("[3] Test Suite (will reset everything!)\n");
        printf("[4] Exit\n");
        select = menuInputInt(1, 4);

        switch (select) {
            // Login
            case 1:
                // loginMenu();
                break;

            // Register
            case 2:
                // registerMenu();
                break;
            
            // Test Suite
            case 3:
                testSuite();
                break;
            
            // Exit
            case 4:
                exit = 1;
                break;

        }

    }

}

int main() {
    chardexLogo();

    printf("=== [ CHARDEX ] ===\n\n");
    
    firstMenu();

    return 0;
}