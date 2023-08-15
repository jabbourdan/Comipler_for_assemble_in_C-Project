#ifndef MACHINECODE_H
#define MACHINECODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "validSyntax.h"
#include "dataTable.h"
struct machineCode {
    char symbol[31];
    char opcode [MAX_BITES];
    char funct [5];
    char functAdress [5];
    char firstArg [MAX_LINE_LENGTH];
    char firstArgAddress[MAX_BITES];
    char secondArg [MAX_LINE_LENGTH];
    char secondArgAddress [MAX_BITES];
    char stringordata[MAX_LINE_LENGTH];
    struct machineCode* next;
};

void machineCodeFunction(struct machineCode *head, char function[], char line[]);
const char* funcBits(char op[]);
void insserTheNumbers(struct machineCode* head,char line[]);
char* changeBinary(int number,int bits);
int isNumeric(const char* str);
void insertNode(struct machineCode* head, const char* symbol, int num);
void insertTheString(struct machineCode* head,char line[]);
void printTheString(struct machineCode* head,const char* token,char* symbol);
void insertnodeString(struct machineCode* head ,const char* symbol,char ch);
int checkBothRegOrNot(const char line[]);
void argFuntion(const char line[],int index, struct machineCode* head,char functionName[]);
void updateTheMachineOfTheFunction(struct dataTable* data,struct machineCode* head,char line[],int isSymbol);
#endif