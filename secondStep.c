#include "secondStep.h"
void printAllMachineCodes(struct machineCode* head) {
    struct machineCode* current = head;
    int i;

    while (current != NULL) {
        printf("The Opcode: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->opcode[i]);
        }
        printf("\nThe First code: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->firstArgAddress[i]);
        }
        printf("\nThe second code: ");
        for (i = 0; i < 12; i++) {
            printf("%c", current->secondArgAddress[i]);
        }
        printf("\n");
        printf("\n");
        current = current->next;
    }
}
void secondCheck(char* fileName,struct dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
    printf("----------------------\n");
    printf("----second step-------\n");
    printf("----------------------\n");
    char line[MAX_LINE_LENGTH];
    int index,var,value,tempIC;
    char fileNameAM[MAX_LINE_LENGTH];
    char fileNameOb[MAX_LINE_LENGTH];
    char fileNameEntry[MAX_LINE_LENGTH];
    char fileNameExtern[MAX_LINE_LENGTH];
    FILE  *fileOb,*fileEntry,*fileExtern,*fileAm;
    strcpy(fileNameAM,fileName);
    size_t fileNameLength = strlen(fileName);
    if (fileNameLength >= 3) {
        fileName[fileNameLength - 3] = '\0';
    }
    snprintf(fileNameOb, sizeof(fileNameOb), "%s.ob", fileName);
    snprintf(fileNameEntry, sizeof(fileNameEntry), "%s.ent", fileName);
    snprintf(fileNameExtern, sizeof(fileNameExtern), "%s.ext", fileName);

    fileAm = open_file(fileNameAM,"r");
    fileOb = fopen(fileNameOb,"w");
    fprintf(fileOb , "   %d  %d \n",*IC-*DC-1-100 , *DC);
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

        if (isSymbol(line, temp, dataTail, 2)) {
            while (isspace(line[index]))
                index++;
            while (!isspace(line[index]))
                index++;
            if (stringOrData(line, index)) {
                value = stringOrData(line, index);
                tempIC = tempIC + value;
                continue;
            } else if (entryOrExtery(line, index)) {
                if (entryOrExtery(line, index) == 1) {//extern
                    checkTheExtern(dataTail, line, index);
                } else if (entryOrExtery(line, index) == 2) {
                    checkTheEntry(dataTail, line, index);
                }
            } else index = opCode(line, index, machineTemp);
            if (index == -1) {
                continue;
            }
            tempIC++;
            updateTheMachineOfTheFunction(dataTail, machineTail, line,1,tempIC);
        }
        else if (entryOrExtery(line, index)) {
            if (entryOrExtery(line, index) == 1) {//extern
                checkTheExtern(dataTail, line, 0);
            } else if (entryOrExtery(line, index) == 2) {
                checkTheEntry(dataTail, line, 0);
            }
            free(temp);
            free(machineTemp);
        }else if(stringOrData(line,index)){
            value = stringOrData(line, index);
            tempIC = tempIC + value;
            continue;
        }else{
            index = opCode(line, index, machineTemp);
            if (index == -1) {
                continue;
            }
            tempIC++;
            updateTheMachineOfTheFunction(dataTail, machineTail, line, 0,tempIC);
        }
    }
    printf("END");
    printAllMachineCodes(machineTail);
}