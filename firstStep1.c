
#include <stdio.h>
#include "firstStep1.h"

int NotExistSymbol(struct  Stable* tail , char sname[]) /*Checks if the symbol already exists*/
{
    struct  Stable* tailf = NULL;
    tailf = (struct Stable*)malloc(sizeof(struct Stable));
    tailf = tail;
    while (tailf != NULL)  /*Run on all the symbols we have already found*/
    {
        if (!strcmp(tailf->symbol , sname))
        {
            return 0;
        }
        tailf = tailf->next;
    }
    return 1;
}
int DcData(char line[] , int index, struct  Decode* dhead) /*Summarize the number of values in the data prompt*/
{
    int dccounter = 1;
    while (line[index] != '\0')
    {
        if(line[index] == 44)
            dccounter++;
        index++;
    }
    return dccounter ;
}
int DcString(char line[] , int index, struct  Decode* dhead) /*Summarize the number of chars in the string prompt*/
{
    int dccounter = 0;
    while(isspace(line[index]))
        index ++;
    if (line[index] == 34)
    {
        index = index + 1;
        while (line[index] != 34 && line[index] != '\n' )
        {
            index++;
            dccounter++;
        }
    }
    return dccounter + 1;

}
int DataOrString(char line[] , int index, struct  Decode* dhead) /*Checks whether this is a data prompt or a string prompt, if so returns the space to be allocated for them*/
{
    int aindex = 0;
    char att[MAX];
    if(line[index] == '\n')
        return 0;
    memset(att, '\0' , MAX);
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    if(!strcmp(".data",att))
        return(DcData(line , index, dhead));
    if (!strcmp(".string",att))
        return(DcString(line , index, dhead));
    return 0;

}
int IsSymbol(char line[] , struct  Stable* temp,struct  Stable* tail, struct  Decode* dhead) /*Checks whether a new symbol is being declared*/
{
    int index = 0 , sindex = 0;
    char sname[MAX];
    memset(sname, '\0' , MAX);
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
        if (NotExistSymbol(tail , sname))
        {
            strcpy(temp->symbol,sname);
            strcpy(temp->attributes,"0000");
            temp->attributes[0] = temp->attributes[0] + DataOrString(line,index+1,dhead);
            return 1;
        }
        else
        {
            printf("error: %s already exist \n" , sname );
        }
    }
    return 0;

}

int firstCheck(int IJ, char *argv[], struct  Stable* shead, struct  Decode* dhead, int *IC, int *DC)
{
    int value, index = 0, errorflag = 0;
    int tempDC = 0 , tempIC = 100 ;
    char line[MAX];
    char fname[MAX];
    FILE *fpr;
    struct  Stable* tail= NULL;
    struct  Decode* endd= NULL;
    tail = (struct Stable*)malloc(sizeof(struct Stable));
    tail = shead;
    memset(line, '\0' , MAX);
    strcpy(fname,argv[IJ]);
    strncat(fname, ".am", 3);
    fpr = fopen(fname,"r");
    while (fgets(line, MAX, fpr))
    {
        struct  Decode* dtemp= NULL;
        struct  Stable* temp = NULL;
        dtemp = (struct Decode*)malloc(sizeof(struct Decode));
        temp = (struct Stable*)malloc(sizeof(struct Stable));
        strcpy(dtemp->symbol,"null");
        if(IsSymbol(line,temp,tail,dtemp))
        {
            dhead->next = dtemp;
            dhead =  dhead->next;
            strcpy(dtemp -> symbol, temp->symbol);
            temp ->value = tempIC;
            temp ->baseaddress = tempIC - tempIC %16;
            temp ->offset = tempIC % 16;
            shead ->next = temp;
            shead =  shead->next;
            while(isspace(line[index]))
                index++;
            while(!isspace(line[index]))
                index++;

        }
    }
    fclose(fpr);
    endd = (struct Decode*)malloc(sizeof(struct Decode));
    dhead->next = endd;
    *IC = tempIC;
    *DC = tempDC;
    return errorflag;
}