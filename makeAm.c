#include "makeAm.h"
#include "mcroValid.h"

char* makeAmFile(char* fileSource){
    int length = strlen(fileSource);
    // Allocate memory for the modified string
    char* fileAm = malloc((length + 1) * sizeof(char));
    // Copy the original string to the modified string
    strcpy(fileAm, fileSource);

    // Cut the last two characters
    fileAm[length - 2] = '\0';

    // Append "am" to the modified string
    strcat(fileAm, "am");

    return fileAm;
}


int isMacroOrEndm(char line[]) /*Checks whether it is the beginning of a macro or the end of a macro*/
{
    char* token = strtok(line, " \t\n\r");
    while (token != NULL) {
        if (strcmp(token, "mcro") == 0) {
            return 1;
        }
        if (strcmp(token, "endmcro") == 0) {
            return 2;
        }
        token = strtok(NULL, " \t\n\r");
    }
    return 0;
}


void reWriteAmFile(struct Macro** head, const char* file, const char* fileAm) {
    FILE* sourceFile = open_file(file, "r");
    FILE* destinationFile = open_file(fileAm, "w");
    char line[MAX_LINE_LENGTH];

    int skipLines = 0;
    int found ;
    char str[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), sourceFile) != NULL) {
        strcpy(str,line);
        found = isMacroOrEndm(str);
        if (found == 1) {
            skipLines = 1;
            continue;
        } else if (found == 2) {
            skipLines = 0;

            continue;
        }
        if (skipLines)
            continue;

        int lineModified = 0;
        struct Macro* temp = *head;

        while (temp != NULL) {
            if (strstr(line, temp->name) != NULL) {
                // Replace the word in the line with the macro content
                char* replacedLine = malloc(strlen(line) + strlen(temp->content));
                if (replacedLine == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    fclose(sourceFile);
                    fclose(destinationFile);
                    return;
                }

                strcpy(replacedLine, line);
                char* word = strtok(replacedLine, " \t\n"); // Assuming words are separated by spaces, tabs, or newline

                while (word != NULL) {
                    if (strcmp(word, temp->name) == 0) {
                        // Replace the word with the macro content
                        fprintf(destinationFile, "%s ", temp->content);
                        fprintf(destinationFile, "\n");

                        lineModified = 1;
                    } else {
                        fprintf(destinationFile, "%s ", word);
                    }
                    word = strtok(NULL, " \t\n");
                }

                free(replacedLine);
                break; // Break out of the loop once a match is found
            }
            temp = temp->next;
        }

        // If no match was found, write the original line
        if (!lineModified) {
            fputs(line, destinationFile);
        }
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");

}


struct Macro* createNode(const char* name, const char* content) {
    struct Macro* newNode = (struct Macro*)malloc(sizeof(struct Macro));
    strcpy(newNode->name, name);
    newNode->content = strdup(content);
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Macro* head) {
    struct Macro* current = head;
    while (current != NULL) {
        struct Macro* temp = current;
        current = current->next;
        free((void *) temp->content);
        free(temp);
    }
}


void removeTrailingNewline(struct Macro* head) {
    struct Macro* current = head;
    while (current != NULL) {
        size_t contentLength = strlen(current->content);
        if (contentLength > 0 && current->content[contentLength - 1] == '\n') {
            current->content[contentLength - 1] = '\0';
        }
        current = current->next;
    }
}

int isMacroNameExists(struct Macro* head, const char* name) {
    struct Macro* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Macro name already exists
        }
        current = current->next;
    }
    return 0; // Macro name does not exist in the linked list
}

int insertTheMacro(struct Macro** head, const char* file) {
    char line[100];
    const char* word = "mcro";
    const char* endWord = "endmcro";
    int foundMcro = 0;
    FILE* inputFile = fopen(file, "r");

    if (inputFile == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    // Variables to store the current macro being processed and content reading flag
    struct Macro* newMacro = NULL;
    int isReadingContent = 0;

    // Read each line of the file
    while (fgets(line, sizeof(line), inputFile)) {
        if (strcmp(line, "\n") == 0 && foundMcro && isReadingContent) {
            // Add new line to the content of the current macro
            size_t currentContentLength = strlen(newMacro->content);
            size_t newLineLength = 1;

            // Reallocate memory to accommodate the new line character
            char* newContent = realloc(newMacro->content, currentContentLength + newLineLength + 1);
            if (newContent == NULL) {
                // Memory reallocation failed, handle error
                fclose(inputFile);
                freeList(*head);
                return 1;
            }

            // Append new line character and update the content pointer
            newContent[currentContentLength] = '\n';
            newContent[currentContentLength + newLineLength] = '\0';
            newMacro->content = newContent;
        } else {
            // Check if the line starts with the target word
            if (strncmp(line, word, strlen(word)) == 0) {
                foundMcro = 1;

                char* mcroName = strtok(line + strlen(word), " \t\n\r");
                if (isMacroNameExists(*head, mcroName)) {
                    printf("Macro with name '%s' already exists. Skipping...\n", mcroName);
                    foundMcro = 0;
                    newMacro = NULL;
                    continue; // Skip processing this macro
                }

                // Create a new Macro struct and store the name
                newMacro = createNode(mcroName, "");

                // Set the content reading flag
                isReadingContent = 1;
            } else if (foundMcro && isReadingContent) {
                // Check if the line contains the end word
                if (strstr(line, endWord) != NULL) {
                    // Stop reading the content
                    isReadingContent = 0;

                    // Append the newMacro struct to the linked list
                    if (*head == NULL) {
                        *head = newMacro;
                    } else {
                        struct Macro* current = *head;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                        current->next = newMacro;
                    }

                    // Reset the variables
                    foundMcro = 0;
                    newMacro = NULL;
                } else {
                    // Remove leading spaces and tabs
                    char* contentLine = line;
                    while (*contentLine == ' ' || *contentLine == '\t') {
                        contentLine++;
                    }

                    // Append the line to the content of the current macro
                    size_t currentContentLength = strlen(newMacro->content);
                    size_t lineLength = strlen(contentLine);

                    // Reallocate memory to accommodate the line
                    char* newContent = realloc(newMacro->content, currentContentLength + lineLength + 1);
                    if (newContent == NULL) {
                        // Memory reallocation failed, handle error
                        // You can choose to terminate the program or handle the error gracefully
                        fclose(inputFile);
                        freeList(*head);
                        return 1;
                    }

                    // Append the line and update the content pointer
                    strcat(newContent, contentLine);
                    newMacro->content = newContent;
                }
            }
        }
    }

    fclose(inputFile);

    // Remove the trailing newline from the content of each macro
    removeTrailingNewline(*head);

    return 0;
}
