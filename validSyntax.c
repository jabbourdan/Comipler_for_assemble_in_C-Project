#include "validSyntax.h"

int validSymbol(char line[],char sname[],int indexOfTheDots) {
    int i,j=0;

    if(indexOfTheDots == 0 ){
        printf("\nERROR : The line is : %s \n contain ':' without name\n",line);
        return 0;
    }

    if(indexOfTheDots>=MAX_SYMBOL_LENGTH-1){
        printf("The symbole name : '%s' is larger that 31 its not allowed\n",sname);
        return 0;
    }
    while(isspace(line[j]))
        j++;
    if(isdigit(line[j])){
        printf("The symbol begins with digit, this is the line %s\n",line);
        return 0;}

    for (i = indexOfTheDots; i > 0; i--)
    {
        if(isspace(line[i-1])) {
            printf("ERROR : The line is : %s \n contain space before the : and after the name\n",line);
            return 0;
        }

    }
    if(!isspace(line[indexOfTheDots+1]) || isspace((line[indexOfTheDots-1]))){
        printf("\nERROR : The line is %s \n contain ':' wrong spaces \n",line);
        return 0;
    }

    return 1;
}