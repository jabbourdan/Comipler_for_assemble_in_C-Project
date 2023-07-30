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
        strcpy(new, "-1");
    return new;
}
void machineCodeFunction(struct machineCode* head,char function[],char line[]){
    char *binaryFunction = funcBits(function);
    if(binaryFunction==NULL){
        printf("Error: Memory allocation failed in funcBits \n");
        return;
    }
    if(strcmp(binaryFunction, "-1") == 0){
        printf("Error: the syntax of this line %s Is not correct \n",line);
        return;
    }
    if(binaryFunction !=NULL || binaryFunction != 0){
        strcpy(head->opcode,"000000000000");
        strcpy(head->funct, binaryFunction);
    }
    strcpy(head->funct, binaryFunction);
    free(binaryFunction);
}
char* printBinary(int number, int bits) {
    static char binaryString[13]; // Fixed-size array to store the binary representation (12 bits + 1 null-terminator)

    int i;
    // Check if the number is negative
    if (number < 0) {
        // Calculate the two's complement representation
        number = (1 << bits) + number;
    }

    // Build the binary representation in the character array
    for (i = bits - 1; i >= 0; i--) {
        int bit = (number >> i) & 1;
        binaryString[bits - 1 - i] = bit + '0'; // Convert integer bit to character '0' or '1'
    }

    binaryString[bits] = '\0'; // Null-terminate the string

    return binaryString;
}
int isNumeric(const char* str) {
    if (*str == '-') {
        str++;
    }
    if (*str== '\0') {
        return 0; // Empty string is not numeric
    }
    while (*str && *str != '\n') {
        if (*str < '0' || *str > '9') {
            return 0; // At least one character is not a digit
        }

        str++;
    }
    return 1;
}
void insertNode(struct machineCode* head, const char* symbol, int num) {

    struct machineCode* newNode = (struct machineCode*)malloc(sizeof(struct machineCode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    // Convert the number to binary and store it in the new node
    char* binary = printBinary(num, 12);
    if (binary == NULL) {
        free(newNode); // Free the newly allocated node before returning on error
        return;
    }
    strcpy(newNode->symbol, symbol);
    strcpy(newNode->opcode, binary);
    newNode->next = NULL;

    //free(binary); // Free the binary representation string (since it was dynamically allocated)
    // Find the last node in the linked list
    struct machineCode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the new node to the last node
    head->next = newNode;

}

void isserTheNumbers(struct machineCode* head,char line[],int ind){
    int num,firstTime=0;
    char *binary;
    char* symbol = head->symbol;
    printf("The line is : %s",line);
    char* token = strtok(line, " ,"); // Split the line by spaces and commas
    while (token != NULL) {
        if(isNumeric(token)) {
            if(!firstTime){
                num = atoi(token); // Convert the token to an integer
                //printf("Binary representation of %d: ", num);
                binary = printBinary(num,12);
                strcpy(head->opcode,binary);
                firstTime=1;
            }else {
                num = atoi(token); // Convert the token to an integer
                //printf("Binary representation of %d: ", num);
                binary = printBinary(num,12);
                insertNode(head, symbol, num);
                //strcpy(head->opcode,binary);

                //printf("%s",binary);
                printf("\n");
            }

        }

        token = strtok(NULL, " ,"); // Move to the next token
    }
}
