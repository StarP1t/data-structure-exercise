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

/*
函数名称: init_stack
输出: Stack* s
说明: 动态分配初始化新栈，返回栈指针
*/
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    s->top = -1;
    return s;
}

/*
函数名称: free_stack
输入: Stack* s
说明: 释放栈内数据和栈
*/
void free_stack(Stack* s)
{
    free(s->data);
    free(s);
}

/*
函数名称: is_empty
输入: Stack *s
输出: int 1/0 
说明: 判断是否栈空，是则输出1，否则0
*/
int is_empty(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

/*
函数名称: push
输入: Stack* s, ElemType e
输出: int (status) -1/0
说明: 将元素e压入栈s，若栈满提示并输出-1
*/
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

/*
函数名称: pop
输入: Stack* s, ElemType *e
输出: int (status) -1/0
说明: 将栈顶元素赋值到元素指针内存并出栈，若栈空提示并输出-1
*/
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

/*
函数名称: get_top
输入: Stack* s, ElemType *e
输出: int (status) -1/0
说明: 将栈顶元素赋值到元素指针内存，若栈空提示并输出-1
*/
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
