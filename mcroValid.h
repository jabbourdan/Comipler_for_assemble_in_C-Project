#ifndef MCROVALID_H
#define MCROVALID_H

#include <stdio.h>
#include <string.h>
#include "makeAm.h"

typedef struct {
    char name[MAX_LINE_LENGTH];
} funNotAllowed;

FILE* open_file(const char* file, char* operator);
int isValidRestrictedWord(const char* word);
int validMacro(char* file);
int isThereMcro(char* file);
int checkMacro(char* file);

#endif