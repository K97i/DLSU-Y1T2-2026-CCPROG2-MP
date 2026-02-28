/*

    file_operations.h

    Header file for file_operations.h to use in other parts of the program

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "config_struct.h"

Config getConfig();
int setConfig(Config configWrite);
int resetConfig();

#endif