#ifndef MACHINECODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

struct machineCode {
    char symbol[MAX_LINE_LENGTH];
    char opcode [21];
    char funct [5];
    char sregister [5];
    char saddress[3];
    char dregister [5];
    char daddress [3];
    char ssymbol [MAX_LINE_LENGTH];
    char dsymbol [MAX_LINE_LENGTH];
    char dataorstring[MAX_LINE_LENGTH];
    struct machineCode* next;
};

#endif