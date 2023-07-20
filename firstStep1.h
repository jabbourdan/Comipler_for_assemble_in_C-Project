#ifndef FIRSTSTEP1_H
#define FIRSTSTEP1_H

#define MAX_LINE_LENGTH 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "mcroValid.h"
#include "dataTable.h"
#include "machineCode.h"
#include "validSyntax.h"

// Function prototypes
int stringArg(char line[], int index, struct machineCode* dhead);
int dataArg(char line[], int index, struct machineCode* dhead);
int stringOrData(char line[], int index, struct machineCode* dhead);

int existSymbol(struct dataTable *tail, char sname[]);
int isSymbol(char line[], struct dataTable* temp, struct dataTable* tail, struct machineCode* dhead);

int firstcheck(char* fileName, struct dataTable* shead, struct machineCode* dhead, int* IC, int* DC);

#endif /* FIRSTSTEP1_H */
