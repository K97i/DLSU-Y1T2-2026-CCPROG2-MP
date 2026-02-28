/*

    config_struct.h

    Header file to define the Config struct

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

typedef struct {
    char administratorKey[32]; // 31 characters + null byte
    char encryptionKey[32]; // 31 characters + null byte
} Config;

#endif