#include "firstStep.h"

int is_newline_or_spaces(const char *line) {
    // Check if the line is empty (contains only whitespace characters)
    size_t len = strlen(line);
    size_t i;
    int is_empty = 1;
    for (i = 0; i < len; i++) {
        if (!isspace((unsigned char)line[i])) {
            is_empty = 0;
            break;
        }
    }
    int begins_with_newline = line[0] == '\n';

    return is_empty || begins_with_newline;
}
int isSymbol(char line[], struct dataTable *temp, struct dataTable *dataTable) {
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
        if(validSymbol(line, sname, index)!=1){
            printf("This line %s\nHas Wrong format",line);
        }
        if (validSymbol(line, sname, index)==1) {
            if (notExistSymbol(dataTable, sname)) {
                strcpy(temp->symbol, sname);
                return 1;
            } else {
                printf("\nerror: The symbol %s already exist in the file\n", sname);
            }
        }
    }
    return 0;
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
    return count+1;
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

int stringOrData(char line[],int index) /*Checks whether this is a data prompt or a string prompt, if so returns the space to be allocated for them*/
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

int opCode(char line[], int index, struct machineCode *machineCode) /* Return the index of the opcode, and update the funct in the decode table */
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
    if(!validTakesArgs(opName,line,index)){
        printf("The line %s \nTakes wrong Number of args \n ",line);
        return -1;
    }
    machineCodeFunction(machineCode, opName,line,index);
    argFuntion(line,index,machineCode, opName);
    return index;
}

int extryOrExtery(char line[]){

    int aindex = 0, index = 0 ;
    char att[MAX_LINE_LENGTH];
    if(line[index] == '\n')
        return 0;
    memset(att, '\0' , MAX_LINE_LENGTH);
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    if(!strcmp(".entry",att))
        return(2);
    if(!strcmp(".extern",att))
        return(1);
    return 0;
}
int numOfArg(struct  machineCode* machineCode){
    if(!strcmp(machineCode->funct,"0000") || !strcmp(machineCode->funct,"0001") || !strcmp(machineCode->funct,"0110") || !strcmp(machineCode->funct,"0010") ||!strcmp(machineCode->funct,"0011"))
        return 3;
    else if(!strcmp(machineCode->funct,"0100") || !strcmp(machineCode->funct,"0101") || !strcmp(machineCode->funct,"0111") || !strcmp(machineCode->funct,"1000") || !strcmp(machineCode->funct,"1001") ||
        !strcmp(machineCode->funct,"1010")||!strcmp(machineCode->funct,"1011") || !strcmp(machineCode->funct,"1101") || !strcmp(machineCode->funct,"1100"))
        return 2;
    else if(!strcmp(machineCode->funct,"1111") || !strcmp(machineCode->funct,"1110"))
        return 1;
    else
        return 0;

}

int firstcheck(char *fileName, struct dataTable *dataHead, struct machineCode *machineHead, int *IC, int *DC) {
    int tempDC = 0, tempIC = 100, ind = 0, flagData = 1,flagMachine =1, value,dataTB=0,machineTB=0;
    char line[MAX_LINE_LENGTH];
    FILE *file = open_file(fileName, "r");
    struct dataTable *tail = NULL;
    struct machineCode *tailMachine = NULL;
    tail = (struct dataTable *)malloc(sizeof(struct dataTable));
    tail = dataHead;

    tailMachine=(struct machineCode *)malloc(sizeof(struct machineCode));
    tailMachine=machineHead;

    memset(line, '\0', MAX_LINE_LENGTH);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (is_newline_or_spaces(line)) {
            continue;
        }

        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));
        machineTemp->next = NULL;
        temp->next = NULL;
        if (isSymbol(line, temp, tail)) {
            strcpy(machineTemp->symbol, temp->symbol);
            while (isspace(line[ind]))
                ind++;
            while (!isspace(line[ind]))
                ind++;
            if (stringOrData(line, ind)) {
                if (strstr(line, ".data") != NULL) {
                    if (validateDataSyntax(line, ind)) {
                        value = stringOrData(line, ind);
                        temp->numberOfValues=value;
                        temp->adress=tempIC;
                        insserTheNumbers(machineTemp,line);
                        tempIC = tempIC + value;
                        tempDC = tempDC + value;
                        dataTB=1;
                        machineTB=1;
                    }
                }else if (validString(line, ind)) {
                    value = stringOrData(line, ind);
                    temp->numberOfValues=value;
                    temp->adress=tempIC;
                    insertTheString(machineTemp,line);
                    tempIC = tempIC + value;
                    tempDC = tempDC + value;
                    dataTB=1;
                    machineTB=1;
                }
            }else {
                ind = opCode(line, ind, machineTemp);
                if(ind==-1){
                    continue;
                }
                temp->adress=tempIC;
                tempIC=tempIC + numOfArg(machineTemp);
                dataTB=1;
                machineTB=1;
            }

        }
        else if (stringOrData(line, ind)) {
            if (strstr(line, ".data") != NULL) {
                if (validateDataSyntax(line, ind)) {
                    value = stringOrData(line, ind);
                    insserTheNumbers(machineTemp,line);
                    tempIC = tempIC + value;
                    tempDC = tempDC + value;
                    machineTB=1;
                }
            }else if (validString(line, ind)) {
                value = stringOrData(line, ind);
                insertTheString(machineTemp,line);
                tempIC = tempIC + value;
                tempDC = tempDC + value;
                machineTB=1;
            }
        }else if(extryOrExtery(line) == 2){ //entry
            if(validEntry(line)){
                putTheEntryIn(dataHead,line,flagData,"entry");
                flagData=0;
                dataTB=0;
            }
        }else if(extryOrExtery(line) == 1){//extern
            putTheEntryIn(dataHead,line,flagData,"extern");
            flagData=0;
            dataTB=0;
        }else if(extryOrExtery(line) == 0){//if not entry or extern (if it's a regular function like move ...)
            while(isspace(line[ind])){
                ind++;
            }
<<<<<<< HEAD
            ind = opCode(line, ind, machineTemp);
            if(ind==-1){
                continue;
            }
            machineTB=1;
            temp->adress=tempIC;
            tempIC=tempIC + numOfArg(machineTemp);

=======
>>>>>>> origin/master
        }
        if (flagData&&dataTB) {
            *tail = *temp;
            tail->next = NULL;
            flagData=0;
        } else if(dataTB) {
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next =temp;
        }
        if(flagMachine&&machineTB){
            tailMachine->next =machineTemp;
            tailMachine = tailMachine->next;
            flagMachine = 0;
        }else if(machineTB){
            while (tailMachine->next != NULL) {
                tailMachine = tailMachine->next;
            }
            tailMachine->next = machineTemp;
        }
        ind = 0;
        dataTB=0;
        machineTB=0;

    }
    fclose(file);
    tailMachine = (struct machineCode *) malloc(sizeof(struct machineCode));
    machineHead->next = tailMachine;
    *IC = tempIC;
    *DC = tempDC;
    return 0;
}
