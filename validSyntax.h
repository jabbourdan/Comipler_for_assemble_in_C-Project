#ifndef VALIDSYNTAX_H
#define VALIDSYNTAX_H
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"

#define MAX_SYMBOL_LENGTH 31
int validSymbol(char line[], char sname[], int indexOfTheDots);
int validData(char line[],int ind);
int validString(char line[],int index);
#endif // VALIDSYNTAX_H