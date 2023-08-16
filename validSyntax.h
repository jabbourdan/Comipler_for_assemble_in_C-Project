#ifndef VALIDSYNTAX_H
#define VALIDSYNTAX_H
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include <stdlib.h>
#define MAX_SYMBOL_LENGTH 31
int validSymbol(char line[], int indexOfTheDots);
int validString(char line[],int index);
int returnIndexTheData(char line[],int index);
int validTakesArgs(char functionName[],char line[],int index);
int validateDataSyntax(char line[],int index);
int validEntryAndExtern(char line[],int index);
char* returnDest(char line[],int index);
char* returnSource(char line[],int index);
int validArgsFun(char functionName[],char* firsArg,char* secondArg);
int retrunTheNumberOfThetypeOfThearg(char* arg);
#endif // VALIDSYNTAX_H