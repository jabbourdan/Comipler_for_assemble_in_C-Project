#ifndef DATATABLE_H
#define DATATABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "machineCode.h"
struct dataTable  {
    char symbol [MAX_SYMBOL_LENGTH];
    int numberOfValues;
    int adress;
    int appear;
    char type[8];//if its external or what like step 9
    struct dataTable* next;
};
void putTheEntryOrExternIn(char *errorFileName,struct dataTable * temp,char line[],int flag,const char * type,int index);
int notExistSymbol(char line[],char* errorFileName,struct dataTable *dataTable, char sname[]);
char* extractTheAdressOfSymbol(struct dataTable* head,char* symbol);
void checkTheExtern(char* errorFileName,struct dataTable* head,char line[],int index);
int checkTheEntry(char *errorFileName,struct dataTable *head, char line[],int index);
#endif