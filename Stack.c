#include <stdio.h>
#define MAX_SIZE 100

typedef int ELEM_TYPE;

typedef struct stack
{
    ELEM_TYPE data[MAX_SIZE];
    int top;
} stack;
