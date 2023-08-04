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
int check_comma_between_words(char line[],int i) {
    int firstword=1,word=0,comma = 0;;// Start with 1 to handle the case where the string starts with a word
    while(line[i] != '\0'){
        while(isspace(line[i])){
            i++;
        }
        while(!isspace(line[i]) ){
            if(firstword) {
                word = 1;
                i++;

            }else if(!comma){
                return 0;
            }
            comma = 0;
        }
        firstword=0;
        if(line[i] == ','){
            comma = 1;
        }
    }

    // Check if the last character was a comma


    return 1;
}
int validData(char line[],int index){
    int i;
    index = returnIndexTheData(line,index);
    i=index;

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
    if (lastCharType == 2 ) {
        printf("This line : %s \nEnd with comma its not allowed",line);
        return 0;
    }
    if(check_comma_between_words(line,i) ==0){
        printf("This line : %s \nDont have commas betwen each word",line);
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
char* returnSource(char line[],int index) {
    char *sourceArg = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int sourceIndex = 0;
    if(line[index] == '\n'){
        return NULL;
    }
    while (line[index] != '\0') {
        while (isspace(line[index]) == 0) {
            index++;
        }
        while (line[index] != '\0' || isspace(line[index])) {
            sourceArg[sourceIndex] = line[index];
            sourceIndex++;
            index++;
        }

    }
    if(sourceIndex==0){
        return NULL;
    }
    return sourceArg;
}

char* returnDest(char line[],int index) {
    char *desArg = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int desIndex = 0;
    char c;
    while (line[index] != '\0') {
        while (isspace(line[index]) == 0) {
            index++;
        }
        while (line[index] != '\0' ) {
            index++;
            if(line[index]== ' '){
                break;
            }
        }
        while (line[index] != '\0' || isspace(line[index])) {
            desArg[desIndex] = line[index];
            desIndex++;
            index++;
        }
    }
    if(desIndex==0){
        return NULL;
    }
    return desArg;
}

int validTakesArgs(char functionName[],char line[],int index){
    char* firstArg= returnSource(line,index);
    char* secondArg= returnDest(line,index);
    if(strcmp(functionName, "mov") == 0 || strcmp(functionName, "cmp") == 0 || strcmp(functionName, "add") == 0 || strcmp(functionName, "sub") == 0 || strcmp(functionName, "lea") == 0){
        if(firstArg == NULL || secondArg ==NULL){
            return 0;
        }
    }else if (strcmp(functionName, "not") == 0 || strcmp(functionName, "clr") == 0 || strcmp(functionName, "inc") == 0 || strcmp(functionName, "dec") == 0 || strcmp(functionName, "jmp") == 0 || strcmp(functionName, "bne") == 0 || strcmp(functionName, "red") == 0 || strcmp(functionName, "prn") == 0 || strcmp(functionName, "jsr") == 0){
        if(firstArg==NULL){
            return 0;
        }else if(secondArg != NULL){
            return 0;
        }
    }else if(strcmp(functionName, "rts") == 0 || strcmp(functionName, "stop") == 0){
        if(firstArg!=NULL || firstArg!=NULL){
            return 0;
        }
    }
    free(firstArg);
    free(secondArg);
    return 1;
}

int validFunctionArgs(char functionName[],char line[],int index){
    char* firstArg= returnSource(line,index);
    char* secondArg= returnDest(line,index);

}

int validEntry(char line[]) {

    int index = 0, thereIsword = 0, isWordStart = 1,comma=0;
    while(isspace(line[index]))
        index ++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        index++;
    }
    // Skip leading spaces
    while (isspace(line[index]))
        index++;

    // Check if there are no arguments
    if (line[index] == '\0' || line[index] == '\n') {
        printf("The line: %s\nHas no arguments\n", line);
        return 0;
    }

    while (line[index] != '\0') {
        while (isspace(line[index]))
            index++;


        if (isdigit(line[index])) {
            if (isWordStart) {
                printf("The line : %s has wrong syntax", line);
                return 0; // Word doesn't start with a digit
            }

        }
        while (line[index] && !isspace(line[index]) && line[index]!=',') {
            isWordStart = 0; // Reset the flag when inside a word
            index++;
            comma=0;
            thereIsword =1;
        }



        if(line[index]==','){
            isWordStart = 1;
            comma=1;
        }
        index++;
    }
    return 1;
}