#include "text.h"

#define INIT_STRING_SIZE 124
#define INIT_TEXT_SIZE 16
#define END_LINE 1
#define END_FILE -1
#define BAD_ALLOC 2
#define SUCCESS 0
#define NOTHING_DONE 3

// functions

// string fucs
int createEmptyString(D_string *str)
{
  str->size_used = 0;
  str->size_allocated = INIT_STRING_SIZE;
  str->line = malloc(str->size_allocated);
  if(str->line == NULL)
    return -1;
  else
  {
    str->line[0] = '\0';
    return SUCCESS;
  }
}

int loadLine(FILE *fp, D_string *str)
{
    int c;
    size_t counter = str->size_used;
    while((c = fgetc(fp)) != EOF)
    {
      if((counter + 1) >= str->size_allocated)
      {
        str->size_allocated *= 2;
        char *tmp = realloc(str->line, str->size_allocated);
        if(tmp == NULL)
        return BAD_ALLOC;
        str->line = tmp;
      }
      if(c == '\n')
      {
      str->line[counter] = '\0';
      str->size_used = counter;
      return END_LINE;
      }
      str->line[counter++] = (char)c;
    }
    str->line[counter] = '\0';
    str->size_used = counter;
    return END_FILE;
}

int freeDstring(D_string *str)
{
    if(str == NULL)
    {
        return 0;
    }
    free(str->line);
    str->line = NULL;
    str->size_used = 0;
    str->size_allocated = 0;
    return SUCCESS;
}

int createEmptyD_TEXT(D_TEXT *text)
{   
    text->linesUsed = 0;
    text->linesAllocated = INIT_TEXT_SIZE;
    text->linesArray = malloc(sizeof(D_string) * INIT_TEXT_SIZE); 
    if(text->linesArray == NULL)
    {
        return -1;
    }
    for (size_t i = 0; i < text->linesAllocated; i++) 
    {
    createEmptyString(&text->linesArray[i]);
    }
    return SUCCESS;
    
}

int resizeD_TEXT(D_TEXT *text)
{
    size_t old_size = text->linesAllocated;

    text->linesAllocated *= 2;
    D_string *tmp = realloc(text->linesArray,
    (text->linesAllocated * sizeof(D_string)));
    if(tmp == NULL)
    return BAD_ALLOC;
    text->linesArray = tmp;
    for (size_t i = old_size; i < text->linesAllocated; i++) 
    {
    createEmptyString(&text->linesArray[i]);
    }
    return SUCCESS;
}

int load_D_TEXT(FILE *fp, D_TEXT *text)
{
    int i = text->linesUsed;
    int t_size = text->linesAllocated;
    int flag = loadLine(fp, &text->linesArray[i]);

    
    for(;;)
    {
        if(i >= t_size){
            if(resizeD_TEXT(text) == BAD_ALLOC)
            {
                return BAD_ALLOC;
            }
            t_size = text->linesAllocated;
        }
        flag = loadLine(fp, &text->linesArray[i]);

        if(flag == BAD_ALLOC)
        {
            return BAD_ALLOC;
        }
        else if(flag == END_LINE)
        {
            i++;
            text->linesUsed = i;
        }
        else if(flag == END_FILE)
        {
            i++;
            text->linesUsed = i;
            return END_FILE;
        }
    }
}


int free_D_TEXT(D_TEXT *text)
{
    if(text != NULL)
    {
    for(size_t i = 0; i < text->linesAllocated; ++i)
        {
        free_D_string(&text->linesArray[i]);
        }
        return SUCCESS;
    }
    return NOTHING_DONE;
}

int free_D_string(D_string *str)
{
    if(str->line != NULL)
    {
        free(str->line);
        str->line = NULL;
        str->size_used = 0;
        str->size_allocated = 0;
        return SUCCESS;
    }   
    return NOTHING_DONE;
}

