#include "validSyntax.h"

int validSymbol(char line[],int indexOfTheDots) {
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
    int quat=0;
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
    while (isspace(line[index])) {
        index++;
    }
    while (line[index] != '\0'&&!isspace(line[index])) {
        if(line[index] == ','){
            break;
        }
        sourceArg[sourceIndex] = line[index];
        sourceIndex++;
        index++;
    }
    if(sourceIndex==0){
        return NULL;
    }
    sourceArg[sourceIndex] = '\0';
    return sourceArg;
}

char* returnDest(char line[],int index) {
    char *desArg = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int desIndex = 0;
    if(line[index] == '\n'){
        return NULL;
    }
    while(isspace(line[index]))index++;
    while(!isspace(line[index])){
        if(line[index] == ','){
            index++;
            break;
        }
        index++;
    }
    while (isspace(line[index]) || line[index] ==',') {
        index++;
    }
    while (line[index] != '\0'&&!isspace(line[index])) {
        desArg[desIndex] = line[index];
        desIndex++;
        index++;
    }
    if(desIndex==0){
        return NULL;
    }
    desArg[desIndex] = '\0';
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
        if(firstArg!=NULL || secondArg!=NULL){
            return 0;
        }
    }
    free(firstArg);
    free(secondArg);
    return 1;
}
int retrunTheNumberOfThetypeOfThearg(char* arg){
    int index = 0;
    if(arg==NULL)return 0;
    while(isspace(arg[index]) || arg[index] == ',')index++;
    if(!strcmp(arg,"@r0") || !strcmp(arg,"@r1") || !strcmp(arg,"@r2") || !strcmp(arg,"@r3") || !strcmp(arg,"@r4") ||!strcmp(arg,"@r5") || !strcmp(arg,"@r6") || !strcmp(arg,"@r7")){
        return 5;
    }else if(arg[index] == '-' || isdigit(arg[index])){
        if(arg[index] == '-')index++;
        while(arg[index] != '\0'){
            if(!isdigit(arg[index])){
                printf("The symbol is %s Take wrong type arg\n",arg);
                return 0;
            }
            index++;
        }
        return 1;
    }else if(isalpha(arg[index])){
        return 3;
    }else
        return 0;
}

int validArgsFun(char funcNameSymbol[],char* firstArg,char* secondArg){
    int firstTpye=retrunTheNumberOfThetypeOfThearg(firstArg);
    int secondTpye=retrunTheNumberOfThetypeOfThearg(secondArg);
    if(!strcmp(funcNameSymbol, "mov") || !strcmp(funcNameSymbol, "sub") || !strcmp(funcNameSymbol, "add")){
        if(secondTpye==1){
            printf("The symbol is %s Take wrong type arg\n",funcNameSymbol);
            return 0;
        }
    }else if(!strcmp(funcNameSymbol, "lea")){
        if(firstTpye==1 || firstTpye==5 || secondTpye ==1){
            printf("The symbol is %s Take wrong type arg\n",funcNameSymbol);
            return 0;
        }
    }else if(!strcmp(funcNameSymbol, "not") || !strcmp(funcNameSymbol, "clr") || !strcmp(funcNameSymbol, "inc") || !strcmp(funcNameSymbol, "dec") ||
            !strcmp(funcNameSymbol, "jmp") || !strcmp(funcNameSymbol, "bne") || !strcmp(funcNameSymbol, "red") || !strcmp(funcNameSymbol, "jsr")){
        if(firstTpye==1){
            printf("The symbol is %s Take wrong type arg\n",funcNameSymbol);
            return 0;
        }
    }
    return 1;

}

int validEntryAndExtern(char line[],int index) {
    //valid entry no first number, betwen every 2 word should be comma
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
        if(isdigit(line[index1])){
            printf("This line %s\nHas Wrong format beging with num",line);
            return 0;
        }
        if (num_flag &&  !isspace(line[index1]) && line[index1] != ','){
            printf("This line %s\nHas Wrong format",line);
            return 0;}

        while (!isspace(line[index1]) && line[index1] != ',') {
            num_flag = 1;
            index1++;
        }
        if (line[index1] == ',') {
            num_flag = 0;
        };
        index1++;
    }

    while (line1[index2] != '\0') {
        if (isdigit(line1[index2]) || isalpha(line1[index2])) {
            last_non_space_idx = i;
            comma=0;
        } else {
            if (line[index2] == ',') {
                if (last_comma > last_non_space_idx) {
                    printf("This line %s\nHas Wrong format with comma\n",line);
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