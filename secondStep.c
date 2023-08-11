#include "secondStep.h"

void secondCheck(char* fileName,struct  dataTable* dataTail, struct  machineCode* machineTail,int *IC,int *DC){
    printf("----------------------\n");
    printf("----second step-------\n");
    printf("----------------------\n");
    char line[MAX_LINE_LENGTH];
<<<<<<< HEAD
    char symbol[MAX_SYMBOL_LENGTH];
=======
    int index, sindex = 0;
    char sname[MAX_SYMBOL_LENGTH];
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
    char fileNameAM[MAX_LINE_LENGTH];
    char fileNameOb[MAX_LINE_LENGTH];
    char fileNameEntry[MAX_LINE_LENGTH];
    char fileNameExtern[MAX_LINE_LENGTH];
    FILE  *fileOb,*fileEntry,*fileExtern,*fileAm;
<<<<<<< HEAD
    struct  dataTable* dataHead = NULL;
=======
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
    strcpy(fileNameAM,fileName);
    size_t fileNameLength = strlen(fileName);
    if (fileNameLength >= 3) {
        fileName[fileNameLength - 3] = '\0';
    }
    snprintf(fileNameOb, sizeof(fileNameOb), "%s.ob", fileName);
    snprintf(fileNameEntry, sizeof(fileNameEntry), "%s.ent", fileName);
    snprintf(fileNameExtern, sizeof(fileNameExtern), "%s.ext", fileName);

<<<<<<< HEAD
    printf("----%s\n",fileNameOb);
    printf("----%s\n",fileNameEntry);
    printf("----%s\n",fileNameExtern);
=======
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
    fileAm = open_file(fileNameAM,"r");
    fileOb = fopen(fileNameOb,"w");
    fprintf(fileOb , "   %d  %d \n",*IC-*DC-1-100 , *DC);
    while (fgets(line, MAX_LINE_LENGTH, fileAm)) /* read next line from the file */
    {
        struct machineCode *machineTemp = NULL;
        struct dataTable *temp = NULL;
        struct dataTable *temp1 = NULL;
<<<<<<< HEAD
=======
        index=0;
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
        machineTemp = (struct machineCode *) malloc(sizeof(struct machineCode));
        temp = (struct dataTable *) malloc(sizeof(struct dataTable));
        temp1 = (struct dataTable *) malloc(sizeof(struct dataTable));

<<<<<<< HEAD
        if(isSymbol(line, temp , temp1)){
            printf("The line is %s",line);

=======
        if(isSymbol(line, temp , dataTail,2)){
            while (isspace(line[index]))
                index++;
            while (!isspace(line[index]))
                index++;
            if (stringOrData(line, index)){
                continue;
            }else if(extryOrExtery(line,index)){
                printf("Its entry or extern");
                }
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
        }
        free(temp);
        free(machineTemp);
    }
<<<<<<< HEAD


=======
>>>>>>> 7af2ae3d1fb8fa584c2c10a88b41098fba40298b
}
