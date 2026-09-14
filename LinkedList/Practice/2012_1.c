#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

/* 题目：设计尽可能高效的算法，查找链表储存单词共同后缀的起始位置 */

// 基础定义
// 单向链表定义
typedef struct Node
{
    ElemType data;
    struct Node *link;
} Node;

// 动态初始化
Node* init_list()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->link = NULL;
    return head;
}

// 遍历
void show_list(Node* H)
{
    Node* p = H;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("\n");
}

// 获取长度（含头节点）
int len_list(Node* H)
{
    int len = 0;
    Node* p = H;

    while (p != NULL)
    {
        len++;
        p = p->link;
    }

    return len;
}

// 尾插入
void insert_tail(Node* H, ElemType e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->link = NULL;

    Node* t = H;
    while (t->link != NULL)
        t = t->link;
    t->link = p;
}

// 算法实现
// 法1：先获取长度差异，再遍历
Node* find_sameword(Node* W1, Node* W2)
{
    int len1 = len_list(W1);
    int len2 = len_list(W2);
    int diff;
    Node* p1, * p2;

    if (len1 >= len2)
    {
        diff = len1 - len2;
        p1 = W1;
        p2 = W2;
    }    
    else
    {
        diff = len2 - len1;
        p1 = W2;
        p2 = W1;
    }

    for (int i = 0; i < diff; i++)
            p1 = p1->link;

    while (p1 != p2)
    {
        p1 = p1->link;
        p2 = p2->link;
    }

    return p1;
}