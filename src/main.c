/*

	main.c
	
	Main file for the program
	
	Author: EBORDE, Mikaelo D.
	Last Modified: 3-28-2026
*/


#include <stdio.h>

#include "test_suite.h"
#include "string_helpers.h"
#include "logo.h"
#include "login_register.h"
#include "file_operation.h"
#include "reset_databases.h"

/*
    There are 2 hard problems in computer science: cache invalidation, naming things, and off-by-1 errors.
    - Leon Bambrick
*/

/*

	@name	firstMenu();

    @brief	First screen for user

    @param	userData	Pointer to the user database data
    @param	config      Pointer to the configuration data

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
        printf("[5] Reset Databases\n");
        printf("[6] Exit Program\n");
        printf("\n");
        select = menuInputInt(1, 6);

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
            
            // Reset
            case 5:
                resetDatabases(userData, config);
                break;
            
            // Exit
            case 6:
                exit = 1;
                break;

        }

    }

}

/*

    @name	main();

    @brief	Entrypoint of program

*/
int main() {
    // Load configs, userdata
    Config config = getConfig();
    UserData userData = { 0 };
    getUsers(&userData);

    chardexLogo(); // calls the function to print the program logo
    
    firstMenu(&userData, &config);

    return 0;
}