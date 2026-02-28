<h1 align="center">CCPROG2 - MP Project</h1>
<p align="center">
    <text style="font-weight: bold;"> Chardex (Charmander + Pokedex, working title)</text><br/>
    <text style="font-style: italic;">Authors:</text> <br/>
    EBORDE, Mikaelo<br/>
    SACRAMENTO, Yvan <br/>
</p>

Chardex is a fauna \[1\] database inspired by the Pokemon tool, the Pokedex, and the crowd-sourced, community-driven encyclopedia, Wikipedia. It is a program that scientists of a region of the world can use to store information about the fauna of said region.

\[ 1 \] - "Fauna is the animals characteristic of a region, period, or special environment" - Merriam-Webster Dictionary

# Run Locally

1. Open Powershell in this folder (`cd`, File Explorer Navigation Bar => `powershell`, right-click in folder => "Open Terminal" (Windows 11))
2. Run the following:
```ps
cls ; gcc -Wall -std=c99 -o chardex ./src/*.c ; ./chardex.exe
```

# Features and Implementations

## User Registration

New visitors may register as a regular user to the program (with a username and password). New administrators may register, provided a modifiable override key is inputted. Either category of users may reset their password, given an override key is provided.

## User Data Encryption

Sensitive user data is encrypted using XOR with elements: password, username, and a modifiable encryption key.

## CRUDing Data to and from files

All databases (user data: structs of users, key database: struct of species) will be stored into binary files.

## Calculations

Every species will have an average of each parameter (height, weight, etc.) if administrators have given an array of specimens. Otherwise, it will accept a numerical input.

## Sorting and Search

The animal database (array of structs) will be sorted by name using selection sort, which would allow for a faster binary search by regular users.
