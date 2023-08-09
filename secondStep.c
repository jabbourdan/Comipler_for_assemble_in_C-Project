#include "secondStep.h"

void secondCheck(char* fileName,struct  dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
    printf("----------------------\n");
    printf("----second step-------\n");
    printf("----------------------\n");
    char line[MAX_LINE_LENGTH];
    char symbol[MAX_SYMBOL_LENGTH];
    char fileNameAM[MAX_LINE_LENGTH];
    char fileNameOb[MAX_LINE_LENGTH];
    char fileNameEntry[MAX_LINE_LENGTH];
    char fileNameExtern[MAX_LINE_LENGTH];
    FILE  *fileOb,*fileEntry,*fileExtern,*fileAm;
    struct  dataTable* dataHead = NULL;
    strcpy(fileNameAM,fileName);
    size_t fileNameLength = strlen(fileName);
    if (fileNameLength >= 3) {
        fileName[fileNameLength - 3] = '\0';
    }
    snprintf(fileNameOb, sizeof(fileNameOb), "%s.ob", fileName);
    snprintf(fileNameEntry, sizeof(fileNameEntry), "%s.ent", fileName);
    snprintf(fileNameExtern, sizeof(fileNameExtern), "%s.ext", fileName);

    printf("----%s\n",fileNameOb);
    printf("----%s\n",fileNameEntry);
    printf("----%s\n",fileNameExtern);
    fileAm = open_file(fileNameAM,"r");
    fileOb = fopen(fileNameOb,"w");
    fprintf(fileOb , "   %d  %d \n",*IC-*DC-1-100 , *DC);
    while (fgets(line, MAX_LINE_LENGTH, fileAm)) /* read next line from the file */
    {
        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        struct dataTable *temp1 = NULL;
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));
        temp1 = (struct dataTable *) malloc(sizeof(struct dataTable));

        if(isSymbol(line, temp , temp1)){
            printf("The line is %s",line);

        }
        free(temp);
        free(machineTemp);
    }


}
