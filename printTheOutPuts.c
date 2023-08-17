#include "printTheOutPuts.h"

int returnIfThereIsNoErrors(char* filename) {
    FILE* file = fopen(filename, "r");

    fseek(file, 0, SEEK_END); // Move to the end of the file
    if (ftell(file) == 0 || file==NULL) {
        printf("File is empty.\n");
        fclose(file);
        return 1; // Return code for empty file
    }else
        //printf("File is not empty.\n");

    fclose(file);
    //
    return 0; // Return code for non-empty file
}


void printTheObFile(char *fileName,int *IC,int *DC){
    char fileNameOb[MAX_LINE_LENGTH];
    FILE *fileOb;
    size_t fileNameLength = strlen(fileName);
    if (fileNameLength >= 3) {
        fileName[fileNameLength - 3] = '\0';
    }
    snprintf(fileNameOb, sizeof(fileNameOb), "%s.ob", fileName);
    fileOb = fopen(fileNameOb,"w");
    fprintf(fileOb , "   %d  %d \n",*IC-*DC-1-100 , *DC);

    fclose(fileOb);
}
