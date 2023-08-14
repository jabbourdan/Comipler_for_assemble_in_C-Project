#include "secondStep.h"
void printAllMachineCodes(struct machineCode* head) {
    struct machineCode* current = head;
    while (current != NULL) {
        if (current == NULL) {
            printf("Node is NULL\n");
            return;
        }

        printf("Funcname: %s\n", current->symbol);
        printf("Opcode: %s\n", current->opcode);
        printf("Funct: %s\n", current->funct != NULL ? current->funct : ".");
        printf("FunctAdress: %s\n", current->functAdress != NULL ? current->functAdress : ".");
        printf("FirstArgAddress: %s\n", current->firstArgAddress != NULL ? current->firstArgAddress : ".");
        printf("SecondArgAddress: %s\n", current->secondArgAddress != NULL ? current->secondArgAddress : ".");
        printf("\n");;
        current = current->next;
    }
}
void secondCheck(char* fileName,struct dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
    printf("----------------------\n");
    printf("----second step-------\n");
    printf("----------------------\n");
    char line[MAX_LINE_LENGTH];
    int index, sindex = 0,var;
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
                continue;
            } else if (extryOrExtery(line, index)) {
                if (extryOrExtery(line, index) == 1) {//extern
                    checkTheExtern(dataTail, line, index);
                } else if (extryOrExtery(line, index) == 2) {
                    checkTheEntry(dataTail, line, index);
                }
            } else var = opCode(line, index, machineTemp);
            if (var == -1) {
                continue;
            }
            updateTheMachineOfTheFunction(dataTail, machineTail, line,1);
        } else if (extryOrExtery(line, index)) {
            if (extryOrExtery(line, index) == 1) {//extern
                checkTheExtern(dataTail, line, 0);
            } else if (extryOrExtery(line, index) == 2) {
                checkTheEntry(dataTail, line, 0);
            }
            free(temp);
            free(machineTemp);
        }else if(stringOrData(line,index)){
            continue;
        }else{
            var = opCode(line, index, machineTemp);
            if (var == -1) {
                continue;
            }
            updateTheMachineOfTheFunction(dataTail, machineTail, line,0);
        }

    }
    printf("END");
    printAllMachineCodes(machineTail);
}