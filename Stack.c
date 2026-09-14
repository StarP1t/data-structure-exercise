#include <stdio.h>
#define MAX_SIZE 100
typedef int ElemType;

typedef struct stack
{
    ElemType data[MAX_SIZE];
    int top;
} stack;

