#include <stdio.h>

#include "test_suite.h"
#include "string_helpers.h"
#include "logo.h"
#include "login_register.h"
#include "file_operation.h"

/*
    There are 2 hard problems in computer science: cache invalidation, naming things, and off-by-1 errors.
    - Leon Bambrick
*/

void firstMenu(UserData *userData, Config *config) {
    int exit = 0, select = 0;

    // while not exit...
    while (!exit) {
        printf("=== [ CHARDEX ] ===\n\n");
        printf("[1] Login\n");
        printf("[2] Register\n");
        printf("[3] Reset Password\n");
        printf("[4] Test Suite (will reset everything!)\n");
        printf("[5] Exit\n\n");
        select = menuInputInt(1, 5);

        printf("\n");

        switch (select) {
            // Login
            case 1:
                loginMenu(userData, config);
                break;

            // Register
            case 2:
                registerMenu(userData, config);
                break;

            // Password Reset
            case 3:
                resetPasswordMenu(userData, config);
                break;
            
            // Test Suite
            case 4:
                testSuite();
                break;
            
            // Exit
            case 5:
                exit = 1;
                break;

        }

    }

}

int main() {
    // Load Params
    Config config = getConfig();
    UserData userData = { 0 };
    getUsers(&userData);

    chardexLogo();
    
    firstMenu(&userData, &config);

    return 0;
}