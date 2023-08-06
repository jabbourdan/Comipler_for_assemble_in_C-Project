#include "validSyntax.h"

int validSymbol(char line[],char sname[],int indexOfTheDots) {
    int j=0;

    if(indexOfTheDots == 0 ){
        //printf("\nERROR : The line is : %s \n contain ':' without name\n",line);
        return -1;
    }

    while(isspace(line[j]))
        j++;
    if(isdigit(line[j])){
        //printf("The symbol begins with digit, this is the line %s\n",line);
        return 0;}
    if(indexOfTheDots-j>=MAX_SYMBOL_LENGTH-1){
        //printf("The symbole name : '%s' is larger that 31 its not allowed\n",sname);
        return -1;
    }
    if(!isspace(line[indexOfTheDots+1]) || isspace((line[indexOfTheDots-1]))){
        //("\nERROR : The line is %s \n contain ':' wrong spaces \n",line);
        return -1;
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
int validateDataSyntax(char line[],int index) {
    int index1 = returnIndexTheData(line,index);
    int num_flag = 0,comma=0;
    int last_non_space_idx = 0,num=0;
    int i = 0;
    int index2=returnIndexTheData(line,index);
    char *line1=line;
    char *line2=line;
    int last_comma = -2;
    while (line[index1] != '\0') {
        if (isspace(line[index1])) {
            index1++;
            continue;
        }
        if (num_flag &&  isdigit(line[index1])){
            printf("This line %s\nHas Wrong format",line);
            return 0;}
        while (isdigit(line[index1])) {
            num_flag = 1;
            index1++;
        }
        if (line[index1] == ',') {

            num_flag = 0;
        };
        index1++;
    }
    /* second run adjacent comma check*/
    while (line1[index2] != '\0') {
        if (isdigit(line1[index2]) || isalpha(line1[index2])) {
            last_non_space_idx = i;
            comma=0;
        } else {
            if (line[index2] == ',') {
                if (last_comma > last_non_space_idx) {
                    printf("This line %s\nHas Wrong format\n",line);
                    return 0;
                }
                last_comma = i;
                comma=1;
            }
        }
        index2++;
        i++;
    }
    i= returnIndexTheData(line,index);
    while(line2[i]!='\0'){
        if(isspace(line2[i]))i++;
        if(line2[i] == ','&& !num){
            printf("This line %s\nHas Wrong format with first comma\n",line);
            return 0;
        }
        if(!isspace(line[i])&&line[i] != ','){
            num=1;
        }
        i++;
    }
    if(comma){
        printf("This line %s\nHas Wrong format\n",line);
        return 0;
    }
    return 1;
}

int validString(char line[],int index){
    int quat=0,first=0;
    index = returnIndexTheData(line,index);
    while(isspace(line[index])){
        index++;
    }
    while(line[index] != '\0') {

        if (line[index] == '"') {
            if (quat == 0) {
                quat = 1;
            } else if (quat==1){
                quat=2;
            }
        }
        index++;
    }
    if(quat==1){
        printf("This line %s \"Has wrong syntax ",line);
        return 0;
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
    //valid entry no first number, betwen every 2 word should be comma
    /*int index = 0, sindex = 0,startOfTheSymbol=0;
    int entry = 0;
    char sname[MAX_LINE_LENGTH];
    memset(sname, '\0', MAX_LINE_LENGTH);
    if (line[index] == '\n')
        return 0;
    while (isspace(line[index]))
        index++;
    while (line[index] != '\n') {
        if (isspace(line[index]) || line[index] == ',')
            break;
        sname[sindex] = line[index];
        sindex++;
        index++;
    }
    while (isspace(line[index]))
        index++;
    printf("-----%s\n", sname);
    while (line[index] != '\0') {

        while(isspace(line[index])){
            startOfTheSymbol=0;
            index++;
        }
        if(isdigit(line[index]) && startOfTheSymbol){
            printf("This line %s\nThe symbol start with a number",line);
            return 0;
        }

    }*/
    return 1;
}