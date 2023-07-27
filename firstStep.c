#include "firstStep.h"


int isSymbol(char line[], struct dataTable *temp, struct dataTable *tail, struct dataTable *dataTable,
             struct machineCode *dhead) {
    int index = 0, sindex = 0;
    char sname[MAX_LINE_LENGTH];
    memset(sname, '\0', MAX_LINE_LENGTH);
    if (line[index] == '\n')
        return 0;
    while (isspace(line[index]))
        index++;
    while (line[index] != '\n' && line[index] != ':') {

        if (line[index] == ":")
            break;
        sname[sindex] = line[index];
        sindex++;
        index++;
    }

    if (line[index] == ':') {
        if (validSymbol(line, sname, index)) {
            if (notExistSymbol(dataTable, sname)) {
                strcpy(temp->symbol, sname);
                strcpy(temp->attributes, "0000");
                temp->attributes[0] = temp->attributes[0] + stringOrData(line, index + 1);
                return 1;
            } else {
                printf("\nerror: The symbol %s already exist in the file\n", sname);
            }
        }

    }
    return 0;
}

int notExistSymbol(struct dataTable *dataTable, char sname[]) /*Checks if the symbol already exists*/
{
    struct dataTable *tailf = NULL;
    tailf = (struct dataTable *) malloc(sizeof(struct dataTable));
    tailf = dataTable;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol, sname)) {
            return 0;
        }
        tailf = tailf->next;
    }
    free(tailf);

    return 1;
}

int stringArg(char line[], int index)/*Summarize the number of chars in the string prompt*/
{
    int count = 0;
    while (isspace(line[index]))
        index++;
    if (line[index] == 34) {
        index = index + 1;
        while (line[index] != 34 && line[index] != '\n') {
            index++;
            count++;
        }
    }
    return count + 1;

}

int dataArg(char line[], int index) /*Summarize the number of values in the data prompt*/
{
    int count = 1;
    while (line[index] != '\0') {
        if (line[index] == 44)
            count++;
        index++;
    }
    return count;
}

int stringOrData(char line[],
                 int index) /*Checks whether this is a data prompt or a string prompt, if so returns the space to be allocated for them*/
{
    int aindex = 0;
    char att[MAX_LINE_LENGTH];
    if (line[index] == '\n')
        return 0;
    memset(att, '\0', MAX_LINE_LENGTH);
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index]) && line[index] != '\n') {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    if (!strcmp(".data", att)) {
        return (dataArg(line, index));
    }

    if (!strcmp(".string", att))
        return (stringArg(line, index));
    return 0;

}

int opCode(char line[], int index,
           struct machineCode *machineCode) /* Return the index of the opcode, and update the funct in the decode table */
{
    int oindex = 0;
    char opName[MAX_LINE_LENGTH];
    memset(opName, '\0', MAX_LINE_LENGTH);
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index])) {
        opName[oindex] = line[index];
        oindex++;
        index++;
    }
    machineCodeFunction(machineCode, opName);
    return index;
}

int firstcheck(char *fileName, struct dataTable *dataHead, struct machineCode *machineHead, int *IC, int *DC) {
    int tempDC = 0, tempIC = 100, ind = 0, flag = 1, value;
    char line[MAX_LINE_LENGTH];
    FILE *file = open_file(fileName, "r");
    struct dataTable *tail = NULL;
    struct machineCode *endd = NULL;
    tail = (struct dataTable *) malloc(sizeof(struct dataTable));
    tail = dataHead;
    memset(line, '\0', MAX_LINE_LENGTH);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));
        strcpy(machineTemp->symbol, "null");
        if (isSymbol(line, temp, tail, dataHead, machineTemp)) {
            machineHead->next = machineHead;
            machineHead = machineHead->next;
            strcpy(machineTemp->symbol, temp->symbol);
            machineTemp->next = NULL;
            temp->value = tempIC;
            temp->baseaddress = tempIC - tempIC % 16;
            temp->offset = tempIC % 16;
            temp->next = NULL;
            if (flag) {
                *tail = *temp;
                tail->next = NULL;
                flag = 0;
            } else {
                tail->next = temp;
                tail = tail->next;
            }
            while (isspace(line[ind]))
                ind++;
            while (!isspace(line[ind]))
                ind++;

            if (stringOrData(line, ind)) {
                if (strstr(line, ".data") != NULL) {
                    if (validData(line, ind)) {
                        value = stringOrData(line, ind);
                        tempDC = tempDC + value;
                        tempIC = tempIC + value;
                    } else if (validString(line, ind)) {
                        value = stringOrData(line, ind);
                        tempDC = tempDC + value;
                        tempIC = tempIC + value;
                    }
                }
            }else {
                ind = opCode(line, ind, machineTemp);
                //tempIC = tempIC + Instruction(line,ind,dtemp);
            }
            ind = 0;
        }
    }
    fclose(file);
    endd = (struct machineCode *) malloc(sizeof(struct machineCode));
    machineHead->next = endd;
    *IC = tempIC;
    *DC = tempDC;
    return 0;
    }
