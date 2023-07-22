#ifndef FIRSTCHECK_H
#define FIRSTCHECK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "mcroValid.h"
#include "dataTable.h"
#include "machineCode.h"
#include "validSyntax.h"
#define MAX 100
int NotExistSymbol(struct Stable* tail, char sname[]);
int DcData(char line[], int index, struct Decode* dhead);
int DcString(char line[], int index, struct Decode* dhead);
int DataOrString(char line[], int index, struct Decode* dhead);
int IsSymbol(char line[], struct Stable* temp, struct Stable* tail, struct Decode* dhead);
int firstCheck(int IJ, char* argv[], struct Stable* shead, struct Decode* dhead, int* IC, int* DC);

#endif /* FIRSTCHECK_H */