#include "dataTable.h"
int notExistSymbol(struct dataTable *dataTable, char sname[]) /*Checks if the symbol already exists*/
{
    struct dataTable *tailf = NULL;
    tailf = (struct dataTable *) malloc(sizeof(struct dataTable));
    tailf = dataTable;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol, sname)) {
            if(!strcmp(tailf->type, "entry")){
                return 1;
            }else if (!strcmp(tailf->type, "extern")){
                printf("This symbol %s is external ",sname);
                return 0;
            }
            else
                return 0;
        }
        tailf = tailf->next;
    }
    free(tailf);
    return 1;
}
void putTheEntryIn(struct dataTable* dataHead, char line[],int flag,const char * type) {
    int index = 0,tokenLength;
    char *substring;
    char att[MAX_LINE_LENGTH];
    struct dataTable* temp1 = NULL; // Point to the existing linked list

    memset(att, '\0', MAX_LINE_LENGTH);

    while (isspace(line[index]))
        index++; // skip spaces

    while (!isspace(line[index]))
        index++; // skip the entry

    while (isspace(line[index]))
        index++; // skip the spaces


    substring=&line[index];

    char *token = strtok(substring, " ,");
    while (token != NULL){
        if(!notExistSymbol(dataHead,token)){
            printf("This symbol %s exist in the dataTable\n",token);
            token = strtok(NULL, " ,");
            continue;
        }
        temp1 = (struct dataTable *) malloc(sizeof(struct dataTable));
        temp1->next = NULL;
        tokenLength= strlen(token);
        if (tokenLength > 0 && token[tokenLength - 1] == '\n') {
            // Remove the last character by setting it to \0
            token[tokenLength - 1] = '\0';
        }
        strcpy(temp1->symbol ,token);
        strcpy(temp1->type,type);
        temp1->appear=0;
        if(flag){
            *dataHead = *temp1;
            dataHead->next = NULL;
            flag=0;
        }else {
            while (dataHead->next != NULL) {
                dataHead = dataHead->next;
            }
            dataHead->next = temp1;

        }
        token = strtok(NULL, " ,");
    }
}