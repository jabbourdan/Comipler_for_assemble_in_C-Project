#include "firstStep1.h"

int dataArg(char line[] , int index, struct  machineCode* dhead){
    int dccounter = 1;
    while (line[index] != '\0')
    {
        if(line[index] == 44)
            dccounter++;
        index++;
    }
    return dccounter ;
}
int stringOrData(char line[] , int index, struct  machineCode* dhead) /*Checks whether this is a data prompt or a string prompt, if so returns the space to be allocated for them*/
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
        return(dataArg(line , index, dhead));
    if (!strcmp(".string",att))
        return(stringArg(line , index, dhead));
    return 0;

}
int existSymbol(struct  dataTable* tail , char sname[]) /*Checks if the symbol already exists*/
{
    struct  dataTable* tailf = NULL;
    tailf = (struct dataTable*)malloc(sizeof(struct dataTable));
    tailf = tail;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (strcmp(tailf->symbol , sname)==0)
        {
            return 1;
        }
        tailf = tailf->next;
    }
    //printf("\n ----------------------The line with the name is : %s \n",sname);
    return 0;
}
int isSymbol(char line[], struct  dataTable *temp,struct  dataTable *tail, struct  machineCode* dhead){
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
        if (!existSymbol(tail , sname))
        {
            strcpy(temp->symbol,sname);
            strcpy(temp->attributes,"0000");
            temp->attributes[0] = temp->attributes[0]+ stringOrData(line,index+1,dhead);
            return 1;
        }
        else
        {
            printf("error: %s already exist \n" , sname );
        }
    }
    return 0;
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


int firstcheck(char* fileName, struct  dataTable* shead, struct  machineCode* dhead, int *IC, int *DC){
    char line[MAX_LINE_LENGTH];
    FILE *file = open_file(fileName,"r");
    memset(line, '\0' , MAX_LINE_LENGTH);
    struct  dataTable* temp = NULL;
    struct  machineCode* datatemp= NULL;
    struct  dataTable* tail= NULL;
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        int tempIC = 100 ,tempDC = 0,index=0;
        datatemp = (struct machineCode*)malloc(sizeof(struct machineCode));
        temp = (struct dataTable*)malloc(sizeof(struct dataTable));
        strcpy(datatemp->symbol,"null");
        int x = isSymbol(line,temp,tail,datatemp);
        printf("%d ---",x);
        if(x)
        {
            dhead->next = datatemp;
            dhead =  dhead->next;
            strcpy(datatemp -> symbol, temp->symbol);
            temp ->value = tempIC;
            temp ->baseaddress = tempIC - tempIC %16;
            temp ->offset = tempIC % 16;
            shead ->next = temp;
            shead =  shead->next;

        }
    }
}