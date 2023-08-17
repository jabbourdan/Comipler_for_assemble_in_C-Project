#include "secondStep.h"
void secondCheck(char* fileName,char* errorFileName,struct dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
    printf("----------------------\n");
    printf("----second step-------\n");
    printf("----------------------\n");
    char line[MAX_LINE_LENGTH];
    int index,value,tempIC;
    FILE  *fileAm;
    fileAm = open_file(fileName,"r");

    while (fgets(line, MAX_LINE_LENGTH, fileAm)) /* read next line from the file */
    {
        if (is_newline_or_spaces(line)) {
            continue;
        }
        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        index = 0;
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));

        if (isSymbol(line,errorFileName, temp, dataTail, 2)) {
            while (isspace(line[index]))
                index++;
            while (!isspace(line[index]))
                index++;
            if (stringOrData(line, index,1)) {
                value = stringOrData(line, index,1);
                tempIC = tempIC + value;
                continue;
            } else if (entryOrExtery(line, index)) {
                if (entryOrExtery(line, index) == 1) {//extern
                    checkTheExtern(errorFileName,dataTail, line, index);
                } else if (entryOrExtery(line, index) == 2) {
                    checkTheEntry(errorFileName,dataTail, line, index);
                }
            } else index = opCode(line, errorFileName,index, machineTemp);
            if (index == -1) {
                continue;
            }
            tempIC++;
            updateTheMachineOfTheFunction(errorFileName,dataTail, machineTail, line,1,tempIC);
        }
        else if (entryOrExtery(line, index)) {
            if (entryOrExtery(line, index) == 1) {//extern
                checkTheExtern(errorFileName,dataTail, line, 0);
            } else if (entryOrExtery(line, index) == 2) {
                checkTheEntry(errorFileName,dataTail, line, 0);
            }
            free(temp);
            free(machineTemp);
        }else if(stringOrData(line,index,0)){
            value = stringOrData(line, index,0);
            tempIC = tempIC + value;
            continue;
        }else{
            index = opCode(line,errorFileName, index, machineTemp);
            if (index == -1) {
                continue;
            }
            tempIC++;
            updateTheMachineOfTheFunction(errorFileName,dataTail, machineTail, line, 0,tempIC);
        }
    }
}