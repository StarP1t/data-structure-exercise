#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef int ElemType;

// 栈链
typedef struct Stack
{
    ElemType data;
    struct Stack* next;
} Stack;

// 初始化
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = 0;
    s->next = NULL;
    return s;
}

// 释放栈链
void free_stack(Stack* S)
{
    Stack* p = S;
    Stack* q;

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

// 判断空栈链
int is_empty(Stack* S)
{
    return S->next == NULL;
}

// 压栈（头插法）
int push(Stack* S, ElemType e)
{
    Stack* n = (Stack*)malloc(sizeof(Stack));
    n->data = e;
    n->next = S->next;
    S->next = n;

    return 0;
}

// 出栈
int pop(Stack* S, ElemType *e)
{
    if (S->next == NULL)
    {
        printf("Stack empty!\n");
        return -1;
    }

    Stack* p = S->next;
    *e = p->data;
    S->next = p->next;
    free(p);

    return 0;
}

// 获取栈顶元素
int get_top(Stack* S, ElemType *e)
{
    if (S->next == NULL)
    {
        printf("Stack empty!\n");
        return -1;
    }

    *e = S->next->data;
    return 0;
}