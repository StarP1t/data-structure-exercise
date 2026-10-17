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

/*
函数名称: init_stack
输出: Stack* s
说明: 动态分配初始化新链栈，返回栈头指针
*/
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = 0;
    s->next = NULL;
    return s;
}

/*
函数名称: free_stack
输入: Stack* S
说明: 从栈头开始顺序释放所有节点
*/
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

/*
函数名称: is_empty
输入: Stack *S
输出: int 1/0 
说明: 判断为空链栈，是则输出1，否则0
*/
int is_empty(Stack* S)
{
    return S->next == NULL;
}

/*
函数名称: push
输入: Stack* S, ElemType e
输出: int (status) 0
说明: 新增节点，将元素e插入链栈头节点后
*/
int push(Stack* S, ElemType e)
{
    Stack* n = (Stack*)malloc(sizeof(Stack));
    n->data = e;
    n->next = S->next;
    S->next = n;

    return 0;
}

/*
函数名称: pop
输入: Stack* S, ElemType *e
输出: int (status) -1/0
说明: 将链栈头指针后第一个节点元素赋值到元素指针中并释放节点，若栈空提示并输出-1
*/
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

/*
函数名称: get_top
输入: Stack* S, ElemType *e
输出: int (status) -1/0
说明: 将链栈头指针后第一个节点元素赋值到元素指针，若栈空提示并输出-1
*/
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