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
    struct dataTable* next;
};

#endif