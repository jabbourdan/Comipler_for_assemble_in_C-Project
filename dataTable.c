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
            }if(strcmp(tailf->type, "extern") ==0) {
                tailf = tailf->next;
                printf("This Symbol %s is extern and is exist on the file as symbol",sname);
                continue;
            }
            return 0;
        }
        tailf = tailf->next;
    }
    free(tailf);

    return 1;
}
int checkTheEntry(struct dataTable *head, char line[],int index){
    struct dataTable *current ;
    char* symbols = (char *) malloc(MAX_SYMBOL_LENGTH);
    int  syIndex = 0,apear=0;

    while (isspace(line[index])) {
        index++;
    }
    while(!isspace(line[index])) {
        index++;
    }
    while(line[index]!='\0') {
        memset(symbols,'\0',31);
        apear=0;
        syIndex=0;
        current=head;
        while(isspace(line[index]))index++;
        while (line[index]!='\0') {
            if (line[index] == ',' || isspace(line[index])) {
                index++;
                break;
            }
            symbols[syIndex] = line[index];
            index++;
            syIndex++;
        }
        while (current != NULL) {
            if (strcmp(current->symbol, symbols) == 0) {
                if (strcmp(current->type, "entry")) {
                    //printf("This Symbol %s is entry and is exist on the file as symbol.\n", symbols);
                    apear=1;
                }
                // Stop the loop once the symbol is found
            }
            current = current->next;
        }
        if(apear==0){
            printf("The entry symbole %s don't exist as a symbol in the file\n",symbols);
        }

    }

    free(symbols);
    return apear;
}

void checkTheExtern(struct dataTable *head, char line[],int index) {
    struct dataTable *current ;
    char* symbols = (char *) malloc(MAX_SYMBOL_LENGTH);
    int  syIndex = 0;

    while (isspace(line[index])) {
        index++;
    }
    while(!isspace(line[index])) {
        index++;
    }
    while(line[index]!='\0') {
        memset(symbols,'\0',31);
        syIndex=0;
        current=head;
        while(isspace(line[index]))index++;
        while (line[index]!='\0') {
            if (line[index] == ',' || isspace(line[index])) {
                index++;
                break;
            }
            symbols[syIndex] = line[index];
            index++;
            syIndex++;
        }
        while (current != NULL) {
            if (strcmp(current->symbol, symbols) == 0) {
                if (strcmp(current->type, "extern")) {
                    printf("This Symbol %s is extern and is exist on the file as symbol.\n", symbols);
                }
                // Stop the loop once the symbol is found
            }
            current = current->next;
        }
    }
    free(symbols);
}

char* extractTheAdressOfSymbol(struct dataTable* head,char* symbol,int tempIC){
    char* adress=NULL;
    char* finalAddress=NULL;
    struct dataTable* current = head;
    while (current != NULL) {
        if (strcmp(current->symbol, symbol) == 0) {
            if(strcmp(current->type, "entry") == 0){
                current = current->next;
                continue;
            }else if(strcmp(current->type, "extern") == 0){
                finalAddress = strdup("000000000001");
                return finalAddress;
            }
            finalAddress = (char*)malloc(12);
            if (finalAddress == NULL) {
                printf("Memory allocation failed");
                return 0;
            }
            adress=changeBinary(current->adress,10);
            strcpy(finalAddress, adress);
            strcat(finalAddress, "10");
            break; // Stop the loop once the symbol is found
        }
        current = current->next;
    }
    return finalAddress;
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

        if(!strcmp(token,".extern") || !strcmp(token,".entry")){
            token = strtok(NULL, " ,");
            continue;
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