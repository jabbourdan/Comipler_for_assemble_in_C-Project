#ifndef DATATABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
struct dataTable  {
    char symbol [MAX_LINE_LENGTH];
    int numberOfValues;
    int adress;
    int appear;
    char type[8];//if its external or what like step 9
    struct dataTable* next;
};
void putTheEntryIn(struct dataTable * temp,char line[],int flag);
int notExistSymbol(struct dataTable *dataTable, char sname[]);
#endif