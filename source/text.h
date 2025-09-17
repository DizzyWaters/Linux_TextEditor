#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *line;
    size_t size_used;
    size_t size_allocated;

} D_string;

typedef struct
{
    D_string *linesArray;
    size_t linesUsed;
    size_t linesAllocated;

} D_TEXT;

// functions

// string fucs
int createEmptyString(D_string *str);
int loadLine(FILE *fp, D_string *str);
int freeDstring(D_string *str);
int createEmptyD_TEXT(D_TEXT *text);
int resizeD_TEXT(D_TEXT *text);
int load_D_TEXT(FILE *fp, D_TEXT *text);
int free_D_TEXT();
int free_D_string(D_string *str);








#endif
