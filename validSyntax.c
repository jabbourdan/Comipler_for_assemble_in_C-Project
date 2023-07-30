#include "validSyntax.h"

int validSymbol(char line[],char sname[],int indexOfTheDots) {
    int i,j=0;

    if(indexOfTheDots == 0 ){
        printf("\nERROR : The line is : %s \n contain ':' without name\n",line);
        return 0;
    }

    while(isspace(line[j]))
        j++;
    if(isdigit(line[j])){
        printf("The symbol begins with digit, this is the line %s\n",line);
        return 0;}
    if(indexOfTheDots-j>=MAX_SYMBOL_LENGTH-1){
        printf("The symbole name : '%s' is larger that 31 its not allowed\n",sname);
        return 0;
    }
    if(!isspace(line[indexOfTheDots+1]) || isspace((line[indexOfTheDots-1]))){
        printf("\nERROR : The line is %s \n contain ':' wrong spaces \n",line);
        return 0;
    }
    return 1;
}
int returnIndexTheData(char line[],int index){
    int aindex = 0;
    char att[MAX_LINE_LENGTH];
    memset(att, '\0' , MAX_LINE_LENGTH);
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        att[aindex] = line[index];
        aindex++;
        index++;
    }
    return index;
}
int validData(char line[],int index){

    index = returnIndexTheData(line,index);
    //printf("-----%d-----\n",index);

    int lastCharType = 0,beforeNumber=0; // 0: None, 1: Digit, 2: Comma
    while (line[index] != '\0') {
        if (isdigit(line[index]) || (line[index] == '-' && isdigit(line[index + 1]))) {
            if (lastCharType == 2 && !beforeNumber) {
                printf("This line : %s \nBegins with comma\n",line);
                return 0;
            }
            lastCharType = 1;
            if (line[index] == '-' && !beforeNumber) {
                index++; // Skip the negative sign
            }
            beforeNumber =1;
            while (isdigit(line[index+1])) {
                index++;
                lastCharType = 1;// Skip the digits of the number
            }
        } else if (line[index] == ',') {
            if (lastCharType == 0 || lastCharType == 2) {
                printf("This line : %s \nHas Wrong format with the comma\n",line);
                return 0;
            }
            lastCharType = 2;

        } else if (line[index] != ' ' && line[index] !='\n' ) {
            printf("This line : %s \nContain invalid characters\n",line);
            return 0;
        }

        index++;
    }
    if (lastCharType == 2) {
        printf("This line : %s \nEnd with comma its not allowed",line);
        return 0;
    }

    return 1;
}

int validString(char line[],int index){
    int quat=0;
    index = returnIndexTheData(line,index);
    while(isspace(line[index])){
        index++;
    }
    while(line[index] != '\0') {

        if (line[index] == '"') {
            if (quat == 0) {
                quat = 1;

            } else if (quat == 1) {
                while (isspace(line[index+1])) {
                    index++;
                }
                if (line[index+1] != '\0') {
                    printf("---%c\n",line[index]);
                    printf("This line %s \nHas arguments more the its should be\n", line);
                    return 0;
                }
            }


        }
        index++;
    }
    return 1;
}
