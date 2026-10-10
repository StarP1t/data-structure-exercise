#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5
typedef int ELEM_TYPE;

// 循环队列
typedef struct
{
    ELEM_TYPE* data;
    int front;
    int rear;
    int is_empty;
} Queue;

// 动态初始化队列
Queue* init_queue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * MAX_SIZE);
    q->front = 0;
    q->rear = MAX_SIZE - 1;
    q->is_empty = 1;
}

// 释放队列
int free_queue(Queue* q)
{
    if (!q)
    {
        printf("Null ptr!\n");
        return -1;
    }

    free(q->data);
    free(q);
    return 0;
}

// 入队
int queue(Queue* q, ELEM_TYPE e)
{
    if ((q->rear + 1) % MAX_SIZE == q->front && !q->is_empty)
    {
        printf("Full!\n");
        return -1;
    }

    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = e;
    q->is_empty = 0;
    
    return 0;
}

// 出队
int dequeue(Queue* q, ELEM_TYPE *e)
{
    if (q->is_empty)
    {
        printf("Empty!\n");
        return -1;
    }

    *e = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    if ((q->rear + 1) % MAX_SIZE == q->front)
        q->is_empty = 1;

    return 0;
}

// 测试
int main()
{
    Queue* q = init_queue();
    int e;
    queue(q, 1);
    queue(q, 2);
    queue(q, 3);
    queue(q, 4);
    queue(q, 5);
    queue(q, 5);
    printf("%d %d\n", q->front, q->rear);
    dequeue(q, &e);
    dequeue(q, &e);
    dequeue(q, &e);
    dequeue(q, &e);
    dequeue(q, &e);
    dequeue(q, &e);
    printf("%d %d\n", q->front, q->rear);

    return 0;
}