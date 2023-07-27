#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mcroValid.h"
#include "firstStep.h"

int check_length_lines(char *filename);

int main(int argc, char *argv[]) {
    int i,IC, DC;
    const char *extension_as = ".as";
    int max_length;
    int valid ;
    printf("Number of arguments: %d\n", argc);

    if (argc == 1) {
        fprintf(stderr, "No files given.\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        size_t filenameLength = strlen(argv[i]);
        size_t extensionLength = strlen(extension_as);
        char *fileEnd;
        struct  dataTable* dataHead = NULL;
        //struct  machineCode* machineTail= NULL;
        struct  machineCode* machineHead = NULL;
        dataHead = (struct dataTable*)malloc(sizeof(struct dataTable));
        dataHead->next = NULL;
        machineHead = (struct machineCode*)malloc(sizeof(struct machineCode));
       // machineTail = (struct machineCode*)malloc(sizeof(struct machineCode));
        //machineTail = machineHead;
        machineHead->next = NULL;
        char *file = (char *)malloc((filenameLength + extensionLength + 1) * sizeof(char));
        fileEnd = file;
        strcpy(file, argv[i]);
        strcat(file, extension_as);
        printf("%s\n", file);

        max_length = check_length_lines(file);
        if (max_length <= 0) {
            continue;
        }
        int numMcro = isThereMcro(file);
        if(numMcro > 0){
            valid = checkMacro(file);

            if(valid){
                fileEnd = makeAmFile(file);
                struct Macro* head = NULL;
                insertTheMacro(&head, file);
                reWriteAmFile(&head, file,fileEnd);
                //printList(head);
                freeList(head);

            }
            printf("%s ----\n ",fileEnd);

        }
        firstcheck(fileEnd,dataHead,machineHead,&IC,&DC);


        free(file);
    }
    return 0;
}


int check_length_lines(char* filename) {
    FILE* file;
    char line[MAX_LINE_LENGTH+1];
    int maxLineLength = 0;
    int length_line = 0;

    // Open the file in read mode
    file = fopen(filename, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return -1;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        int lineLength = strlen(line);

        // Remove the newline character at the end of the line
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
            lineLength--;
        }

        // Update the maximum line length if necessary
        if (lineLength > maxLineLength) {
            maxLineLength = lineLength;
        }
    }
    fclose(file);

    length_line = maxLineLength +1;
    if(length_line <=80){
        return 1;
    }
    else
        return 0;
}