#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef int ElemType;

// 栈
typedef struct
{
    ElemType* data;
    int top;
} Stack;

// 动态初始化
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    s->top = -1;
    return s;
}

// 判断空栈
int is_empty(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

// 压栈
int push(Stack* s, ElemType e)
{
    if (s->top >= MAX_SIZE - 1)
    {
        printf("Stack full!\n");
        return -1;
    }

    s->data[++s->top] = e;
    return 0;
}

// 出栈
int pop(Stack* s, ElemType *e)
{
    if (s->top == -1)
    {
        printf("Stack empty!\n");
        return -1;
    }

    *e = s->data[s->top--];
    return 0;
}

// 获取栈顶元素
int get_top(Stack* s, ElemType *e)
{
    if (s->top == -1)
    {
        printf("Stack empty!\n");
        return -1;
    }

    *e = s->data[s->top];
    return 0;
}
