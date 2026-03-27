/*

    config_struct.h

    Header file to define the Config struct

    Author: EBORDE, Mikaelo D.
    Last Modified: 2-28-2026

*/

#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

#define CONFIG_STRING_LEN 31 // 30 characters + null byte

typedef struct {
    char administratorKey[CONFIG_STRING_LEN]; 
    char encryptionKey[CONFIG_STRING_LEN];
} Config;

#endif