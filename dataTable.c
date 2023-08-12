#include "dataTable.h"
int notExistSymbol(struct dataTable *dataTable, char sname[]) /*Checks if the symbol already exists*/
{
    struct dataTable *tailf = NULL;
    tailf = (struct dataTable *) malloc(sizeof(struct dataTable));
    tailf = dataTable;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol, sname)) {
            if(strcmp(tailf->type, "entry") ==0){
                tailf = tailf->next;
                continue;
            }
            return 0;
        }
        tailf = tailf->next;
    }
    free(tailf);

    return 1;
}

int theSymboleIsEntryOrExtern(struct dataTable *dataTable, char sname[]){
    struct dataTable* current = dataTable;
    while (current != NULL && !strcmp(current->symbol, sname)) {
        current = current->next;
    }
    if (current != NULL) {
        current->appear = 1;
        return 1;
    } else {
        printf("Node with target data not found.\n");
    }
    return 0;
}
char* extractTheAdressOfSymbol(struct dataTable* head,char* symbol){
    char* adress=NULL;
    struct dataTable* current = head;
    while (current != NULL) {
        if (strcmp(current->symbol, symbol) == 0) {
            if(strcmp(current->type, "entry") == 0){
                current = current->next;
                continue;
            }else if(strcmp(current->type, "extern") == 0){
                strcpy(adress,"000000000010");
                break;
            }
            adress=changeBinary(current->adress,12);
            break; // Stop the loop once the symbol is found
        }
        current = current->next;
    }
    return adress;
}
void putTheEntryOrExternIn(struct dataTable* dataHead, char line[],int flag,const char * type,int index) {
    int tokenLength;
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