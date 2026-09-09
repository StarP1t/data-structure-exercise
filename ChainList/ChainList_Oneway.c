#include <stdio.h>
#include <stdlib.h>
#define ELEM_TYPE int

// 单向链表
typedef struct Node
{
    ELEM_TYPE data;
    struct Node *next;
} Node;

// 初始化
Node* init_list()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}