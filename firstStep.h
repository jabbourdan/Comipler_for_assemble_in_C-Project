
#ifndef FIRSTSTEP_H
#define FIRSTSTEP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "mcroValid.h"
#include "dataTable.h"
#include "machineCode.h"
#include "validSyntax.h"
#include "secondStep.h"
int isSymbol(char line[], struct  dataTable* temp,struct  dataTable* dataTable,int step);
int firstcheck(char* fileName, struct  dataTable* shead, struct  machineCode* dhead, int *IC, int *DC);
int stringOrData(char line[] , int index);
int stringArg(char line[] , int index);
int dataArg(char line[] , int index);
int opCode(char line[], int ind ,struct  machineCode* machineCode);
int extryOrExtery(char line[],int index);
int numOfArg(struct  machineCode* machineCode,char line[]);
int is_newline_or_spaces(const char *line);
#endif