#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef int ElemType;

// 队列
typedef struct
{
    ElemType* data;
    int front;
    int rear;
} Queue;

// 动态初始化
Queue* init_queue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue*));
    q->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    q->front = 0;
    q->rear = 0;
}

// 调整队列
int adjust_queue(Queue* q)
{
    int step = q->front;
    if (step == 0)
        return 0;
    
    for (int i = q->front; i <= q->rear; i++)
        q->data[i - step] = q->data[i];
    q->front = 0;
    q->rear -= step;

    return 1;
}

// 入队
int queue(Queue* q, ElemType e)
{
    if (!adjust_queue(q))
    {
        printf("Queue is full!\n");
        return -1;
    }

    q->data[q->rear++] = e;
    return 0;
}

// 出队
int dequeue(Queue* q, ElemType* e)
{
    if (q->front == q->rear)
    {
        printf("Queue is empty!\n");
        return -1;
    }

    *e = q->data[q->front++];
    return 0;
}
