#ifndef DATATABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"

struct dataTable {
    char symbol [MAX_LINE_LENGTH];
    int value;
    int baseaddress;
    int offset;
    char attributes [5] ;
    struct dataTable* next;
};

#endif