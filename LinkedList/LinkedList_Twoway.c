#include <stdio.h>
#include <stdlib.h>
#define ELEM_TYPE int

// 双向链表
typedef struct Node
{
    ELEM_TYPE data;
    struct Node *prev, *next;
} Node;

// 动态初始化
Node* init_list()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

// 释放链表
void free_list(Node* H)
{
    Node* p = H;
    Node* q;

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

// 获取长度（含头节点）
int len_list(Node* H)
{
    int len = 0;
    Node* p = H;

    while (p != NULL)
    {
        len++;
        p = p->next;
    }

    return len;
}

// 遍历（正反）
void show_list(Node* H, int is_reverse)
{
    Node* p = H->next;

    if (is_reverse)
    {
        while (p != NULL && p->next != NULL)
            p = p->next;
        while (p->prev != NULL)
        {
            printf("%d ", p->data);
            p = p->prev;
        }
    }
    else
    {
        while (p != NULL)
        {
            printf("%d ", p->data);
            p = p->next;
        }
    }
    printf("\n");
}

// 头插法
int insert_head(Node* H, ELEM_TYPE e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = H->next;
    p->prev = H;

    if (H->next != NULL)
        H->next->prev = p;
    H->next = p;

    return 0;
}

// 尾插法（头节点）
int insert_tail_by_head(Node* H, ELEM_TYPE e)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = e;
    n->next = NULL;

    Node* p = H;
    while (p->next != NULL)
        p = p->next;
    p->next = n;
    n->prev = p;

    return 0;
}

// 尾插法（尾节点）
int insert_tail(Node* T, ELEM_TYPE e)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = e;
    n->next = NULL;
    n->prev = T;
    T->next = n;

    return 0;
}

// 指定位置插入
int insert_index(Node* H, int index, ELEM_TYPE e)
{
    if (index < 0 || index >= len_list(H))
    {
        printf("错误索引\n");
        return -1;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;

    Node* t = H;
    for (int i = 0; i < index - 1; i++)
        t = t->next;

    p->next = t->next;
    p->prev = t;
    t->next = p;
    if (p->next != NULL)
        p->next->prev = p;

    return 0;
}