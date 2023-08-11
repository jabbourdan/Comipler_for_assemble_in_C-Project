#include "mcroValid.h"

funNotAllowed macroNames[16] = {
        {"mov"},
        {"cmp"},
        {"add"},
        {"sub"},
        {"not"},
        {"clr"},
        {"lea"},
        {"inc"},
        {"dec"},
        {"jmp"},
        {"bne"},
        {"red"},
        {"prn"},
        {"jsr"},
        {"rts"},
        {"stop"}
};

FILE* open_file(const char* file, char* operator) {
    FILE* inputFile = fopen(file, operator);
    if (inputFile == NULL) {
        printf("Unable to open the file: %s.\n", file);
    }
    return inputFile;
}
int isValidRestrictedWord(const char* word) {
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(word, macroNames[i].name) == 0) {
            return 0;
        }
    }
    return 1;
}


int validMacro(char* file) {
    char line[MAX_LINE_LENGTH];
    const char* word = "mcro";
    const char* endWord = "endmcro";
    int found = 0;
    int endfound = 0;
    int i;
    FILE* inputFile = open_file(file,"r");

    // Read each line of the file
    while (fgets(line, sizeof(line), inputFile)) {
        // Tokenize the line into words
        char* token = strtok(line, " \t\n\r");

        // Check each word
        while (token != NULL) {
            // Compare the word with the target word
            if (strcmp(token, word) == 0) {
                // Check if there are only spaces or no spaces before the keyword
                int tokenIndex = token - line;
                int validMacro = 1;

                // Check before the keyword
                for (i = 0; i < tokenIndex; i++) {
                    if (line[i] != ' ') {
                        validMacro = 0;
                        break;
                    }
                }

                // Check if the next word exists
                char* nextWord = strtok(NULL, " \t\n\r");


                if (nextWord == NULL || !isValidRestrictedWord(nextWord)) {
                    validMacro = 0;
                    return 0;
                } else {
                    // Check if there are additional words after the next word
                    char* additionalWord = strtok(NULL, " \t\n\r");
                    if (additionalWord != NULL) {
                        validMacro = 0;
                    }
                }
                if (validMacro) {
                    found = 1;
                    break;
                }else
                    found = 0;
                break;

            }

            if (strcmp(token, endWord) == 0) {
                // Check if there are only spaces or no spaces before the keyword
                int tokenIndex = token - line;
                int validEndMacro = 1;

                // Check before the keyword
                for (i = 0; i < tokenIndex; i++) {
                    if (line[i] != ' ') {
                        validEndMacro = 0;
                        break;
                    }
                }

                // Check if there are additional words after the keyword
                char* nextWord = strtok(NULL, " \t\n\r");
                if (nextWord != NULL) {
                    validEndMacro = 0;
                }

                if (validEndMacro) {
                    endfound = 1;
                    break;
                } else {
                    endfound = 0;
                    break;
                }
            }

            token = strtok(NULL, " \t\n\r");
        }




    }

    fclose(inputFile);

    // Print the result
    if (found&endfound) {
        return 1;
    } else {
        return 0;
    }
}

int isThereMcro(char* file){
    const char* targetWord = "mcro";
    FILE* inputFile = open_file(file,"r");
    int index = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), inputFile)) {
        char* token = strtok(line, " \t\n\r");
        while (token != NULL) {
            if (strcmp(token, targetWord) == 0) {
                index++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }
    fclose(inputFile);
    return index;
}

int checkMacro(char* file){
    if(isThereMcro(file)) {
        if (validMacro(file))

            return 1;
    }
    return 0;
}