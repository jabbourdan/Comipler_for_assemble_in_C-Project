#include "machineCode.h"

const char* funcBits(char op[]) /*Returns the opcode type in decimal base*/
{
    char *new = (char*)malloc(5 * sizeof(char));
    if (new == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }
    memset(new, '\0', 5);
    if(!strcmp(op, "mov"))
        strcpy(new, "0000");
    else if(!strcmp(op, "cmp"))
        strcpy(new, "0001");
    else if(!strcmp(op, "add"))
        strcpy(new, "0010");
    else if(!strcmp(op, "sub"))
        strcpy(new, "0011");
    else if(!strcmp(op, "not"))
        strcpy(new, "0100");
    else if(!strcmp(op, "clr"))
        strcpy(new, "0101");
    else if(!strcmp(op, "lea"))
        strcpy(new, "0110");
    else if(!strcmp(op, "inc"))
        strcpy(new, "0111");
    else if(!strcmp(op, "dec"))
        strcpy(new, "1000");
    else if(!strcmp(op, "jmp"))
        strcpy(new, "1001");
    else if(!strcmp(op, "bne"))
        strcpy(new, "1010");
    else if(!strcmp(op, "red"))
        strcpy(new, "1011");
    else if(!strcmp(op, "prn"))
        strcpy(new, "1100");
    else if(!strcmp(op, "jsr"))
        strcpy(new, "1101");
    else if(!strcmp(op, "rst"))
        strcpy(new, "1110");
    else if(!strcmp(op, "stop"))
        strcpy(new, "1111");
    else
        return 0;
    return new;
}
void machineCodeFunction(struct machineCode* head,char function[]){
    char *binaryFunction = funcBits(function);
    if(binaryFunction==NULL){
        printf("Error: Memory allocation failed in funcBits\n");
        return;
    }
    printf("The binnary of the %s is : %s\n",function,binaryFunction);
    if(binaryFunction !=NULL || binaryFunction != 0){
        strcpy(head->opcode,"000000000000");
        strcpy(head->funct, binaryFunction);
    }
    strcpy(head->funct, binaryFunction);
    free(binaryFunction);
}