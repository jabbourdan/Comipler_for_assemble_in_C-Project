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
void putTheEntryOrExternIn(struct dataTable * temp,char line[],int flag,const char * type,int index);
int notExistSymbol(struct dataTable *dataTable, char sname[]);
int theSymboleIsEntryOrExtern(struct dataTable *dataTable, char sname[]);
#endif