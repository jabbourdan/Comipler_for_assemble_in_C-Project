#ifndef MAKE_AM_H
#define MAKE_AM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "validSyntax.h"

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
void removeTrailingNewline(struct Macro* head);
int insertTheMacro(char *errorFileName,struct Macro** head, const char* file);
int isMacroNameExists(struct Macro* head, const char* name);

#endif /* MAKE_AM_H */