#ifndef MACHINECODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

struct machineCode {
    char symbol[31];
    char opcode [13];
    char funct [5];
    char sregister [5];
    char saddress[3];
    char dregister [5];
    char daddress [3];
    char ssymbol [MAX_LINE_LENGTH];
    char dsymbol [MAX_LINE_LENGTH];
    char stringordata[MAX_LINE_LENGTH];
    struct machineCode* next;
};

void machineCodeFunction(struct machineCode* head,char function[]);
const char* funcBits(char op[]);
#endif