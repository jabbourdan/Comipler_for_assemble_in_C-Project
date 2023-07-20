#ifndef MAKE_AM_H
#define MAKE_AM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

struct Macro {
    char name[MAX_LINE_LENGTH];
    char* content;
    struct Macro* next;
};

char* makeAmFile(char* fileSource);
int isMacroOrEndm(char line[]);
void reWriteAmFile(struct Macro** head, const char* file, const char* fileAm);
struct Macro* createNode(const char* name, const char* content);
void freeList(struct Macro* head);
void printList(struct Macro* head);
void removeTrailingNewline(struct Macro* head);
int insertTheMacro(struct Macro** head, const char* file);
int isMacroNameExists(struct Macro* head, const char* name);

#endif /* MAKE_AM_H */
