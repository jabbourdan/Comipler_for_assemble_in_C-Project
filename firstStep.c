#include "firstStep.h"


int isSymbol(char line[], struct  dataTable* temp,struct  dataTable* tail,struct  dataTable* dataTable ,struct  machineCode* dhead){
    int index = 0 , sindex = 0;
    char sname[MAX_LINE_LENGTH];
    memset(sname, '\0' , MAX_LINE_LENGTH);
    if(line[index] == '\n')
        return 0;
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n'  && line[index] != ':')
    {
        sname[sindex] = line[index];
        sindex++;
        index++;
    }
    if(line[index] == ':')
    {
        if (validSymbol(line,sname,index))
        {
            if(notExistSymbol(tail,dataTable,sname)){
                strcpy(temp->symbol,sname);
                strcpy(temp->attributes,"0000");
                temp->attributes[0] = temp->attributes[0]+ stringOrData(line,index+1,dhead);
                return 1;
            }else
            {
                printf("\nerror: The symbol %s already exist in the file\n" , sname );
            }
        }

    }
    return 0;
}
int notExistSymbol(struct  dataTable* tail ,struct  dataTable* dataTable , char sname[]) /*Checks if the symbol already exists*/
{
    struct dataTable* tailf = NULL;
    tailf = (struct dataTable*)malloc(sizeof(struct dataTable));
    tailf = tail;
    tailf->next = NULL;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol , sname))
        {
            return 0;
        }
        tailf = tailf->next;
    }
    //strcpy(tail->symbol,sname);
    //tail->next=NULL;

    return 1;
}
int stringArg(char line[] , int index, struct  machineCode* dhead) /*Summarize the number of chars in the string prompt*/
{
    int count = 0;
    while(isspace(line[index]))
        index ++;
    if (line[index] == 34)
    {
        index = index + 1;
        while (line[index] != 34 && line[index] != '\n' )
        {
            index++;
            count++;
        }
    }
    return count + 1;

}
int dataArg(char line[] , int index, struct  machineCode* dhead) /*Summarize the number of values in the data prompt*/
{
    int count = 1;
    while (line[index] != '\0')
    {
        if(line[index] == 44)
            count++;
        index++;
    }
    return count ;
}
int stringOrData(char line[] , int index, struct  machineCode* dataHead) /*Checks whether this is a data prompt or a string prompt, if so returns the space to be allocated for them*/
{
    int aindex = 0;
    char att[MAX_LINE_LENGTH];
    if(line[index] == '\n')
        return 0;
    memset(att, '\0' , MAX_LINE_LENGTH);
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    if(!strcmp(".data",att))
        return(dataArg(line , index, dataHead));
    if (!strcmp(".string",att))
        return(stringArg(line , index, dataHead));
    return 0;

}


int firstcheck(char* fileName, struct  dataTable* dataHead, struct  machineCode* machineHead, int *IC, int *DC){
    int tempDC = 0 , tempIC = 100,ind ;
    char line[MAX_LINE_LENGTH];
    FILE *file = open_file(fileName,"r");
    struct  dataTable* tail= NULL;
    struct  machineCode* endd= NULL;
    tail = (struct dataTable*)malloc(sizeof(struct dataTable));
    tail = dataHead;
    memset(line, '\0' , MAX_LINE_LENGTH);
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        struct  machineCode* machineTemp= NULL;
        struct  dataTable* temp = NULL;
        machineTemp = (struct machineCode*)malloc(sizeof(struct machineCode));
        temp = (struct dataTable*)malloc(sizeof(struct dataTable));
        strcpy(machineTemp->symbol,"null");
        //strcpy(dataHead->symbol,"null");
        if(isSymbol(line,temp,tail,dataHead, machineTemp))
        {
            machineHead->next = machineHead;
            machineHead =  machineHead->next;
            strcpy(machineTemp -> symbol, temp->symbol);

            temp ->value = tempIC;
            temp ->baseaddress = tempIC - tempIC %16;
            temp ->offset = tempIC % 16;
            temp->next = NULL;
            //dataHead = temp;
            //dataHead =  dataHead->next;
            while(tail->next !=NULL){
                tail->next;
            }
            tail->next = temp;
            tail = tail->next;
            //dataHead = tail;
            //while(isspace(line[ind]))
            //    ind++;
            //while(!isspace(line[ind]))
            //    ind++;
        }

    }
    fclose(file);
    endd = (struct machineCode*)malloc(sizeof(struct machineCode));
    machineHead->next = endd;
    *IC = tempIC;
    *DC = tempDC;

    return 0;
}

    NOTE:
    I enter the var dataTable in the exist..
    contuine from there and make te talif is the dataTable and contionue :!!!!!!!: