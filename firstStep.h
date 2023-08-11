
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


int isSymbol(char line[], struct  dataTable* temp,struct  dataTable* tail,struct  dataTable* dataTable, struct  machineCode* dhead);
int notExistSymbol(struct  dataTable* dataTable , char sname[]);
int firstcheck(char* fileName, struct  dataTable* shead, struct  machineCode* dhead, int *IC, int *DC);
int stringOrData(char line[] , int index);
int stringArg(char line[] , int index);
int dataArg(char line[] , int index);
int opCode(char line[], int ind ,struct  machineCode* machineCode);


#endif