#include "secondStep.h"

void secondCheck(char* fileName,struct  dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
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
        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        index=0;
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));

        if(isSymbol(line, temp , dataTail,2)){
            //changeTheApearInDataTable();
            while (isspace(line[index]))
                index++;
            while (!isspace(line[index]))
                index++;
            if (stringOrData(line, index)){
                continue;
            }else if(extryOrExtery(line,index)) {
                //printf("Its entry or extern\n%s",line);
                continue;
            }else var = opCode(line, index, machineTemp);
                if(var==-1){
                continue;
                }
                updateTheMachineOfTheFunction(dataTail,machineTail,line);
        }
        free(temp);
        free(machineTemp);
    }
    printf("END");
}