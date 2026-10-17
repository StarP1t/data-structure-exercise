#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef int ElemType;

// 链队列
typedef struct
{
    ElemType data;
    struct Node* next;
} Node;

typedef struct
{
    Node* front;
    Node* rear;
} LQueue;

// 动态初始化
LQueue* init_lqueue()
{
    LQueue* q = (LQueue*)malloc(sizeof(LQueue));
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    q->front = node;
    q->rear = node;
    return q;
}

// 释放链队列
int free_lqueue(LQueue* q)
{
    if (q == NULL)
        return -1;

    while (q->front)
    {
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
    free(q);

    return 0;
}

// 判断空链队列
int is_empty_lqueue(LQueue* q)
{
    return q->front == q->rear;
}

// 获取队列长度
int length_lqueue(LQueue* q)
{
    if (q == NULL)
        return -1;
    
    int count = 0;
    Node* p = q->front->next;

    while (p)
    {
        count++;
        p = p->next;
    }

    return count;
}

// 取头元素
int get_head_lqueue(LQueue* q, ElemType *e)
{
    Node* p = q->front->next;
    if (p == NULL)
        return -1;
    *e = p->data;
    return 0;
}

// 入队
int en_lqueue(LQueue *q, ElemType e)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;

    q->rear->next = node;
    q->rear = node;
    return 0;
}

// 出队
int de_lqueue(LQueue *q, ElemType *e)
{
    if (q->front == q->rear)
    {
        printf("Queue is empty!\n");
        return -1;
    }

    Node* node = q->front->next;
    *e = node->data;
    q->front->next = node->next;

    if (node->next == NULL)
        q->rear = q->front;
    
    free(node);
    return 0;
}