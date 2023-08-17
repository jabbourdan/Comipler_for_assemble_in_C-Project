#ifndef PRINTTHEOUTPUTS_H
#define PRINTTHEOUTPUTS_H
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "machineCode.h"
#include "dataTable.h"
int returnIfThereIsNoErrors(char *filename);
void printTheObFile(struct machineCode* machineHead,char *filename,const int *IC,const int *DC);
int checkIfTheEntryOrExtern(struct dataTable* dataHead,char* typeToCheck);
void makeTheEntryAndExtern(struct dataTable* dataHead,struct machineCode* machineCode,char *fileName,char *tpye,char* extenstion);
#endif