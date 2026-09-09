#include <stdio.h>
#include <stdlib.h>
#define ELEM_TYPE int // 涉及printf均使用%d

// 单向链表
typedef struct Node
{
    ELEM_TYPE data;
    struct Node *next;
} Node;

// 动态初始化
Node* init_list()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
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

// 遍历
void show_list(Node* H)
{
    Node* p = H;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
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
        p = p->next;
    }

    return len;
}

// 头插入
void insert_head(Node* H, ELEM_TYPE e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = NULL;

    if (H->next != NULL)
        p->next = H->next;
    H->next = p;
}

// 尾插入
void insert_tail(Node* H, ELEM_TYPE e)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = NULL;

    Node* t = H;
    while (t->next != NULL)
        t = t->next;
    t->next = p;
}

// 指定插入
int insert_index(Node* H, int index, ELEM_TYPE e)
{
    if (index < 0 || index >= len_list(H))
    {
        printf("错误索引\n");
        return -1;
    }
    else if (index == 0)
    {
        printf("不可改变头节点\n");
        return -1;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;

    Node* t = H;
    for (int i = 0; i < index - 1; i++)
        t = t->next;
    p->next = t->next;
    t->next = p;

    return 0;
}

// 删除指定元素
int delete_index(Node* H, int index)
{
    if (index < 0 || index >= len_list(H))
    {
        printf("错误索引\n");
        return -1;
    }
    else if (index == 0)
    {
        printf("不可删除头节点\n");
        return -1;
    }

    Node* p = H;
    Node* q;

    for (int i = 0; i < index - 1; i++)
        p = p->next;
    q = p->next;
    p->next = q->next;
    printf("delete:%d\n", q->data);
    free(q);

    return 0;
}

// 改变指定元素
int replace_index(Node* H, int index, ELEM_TYPE e)
{
    if (index < 0 || index >= len_list(H))
    {
        printf("错误索引\n");
        return -1;
    }
    else if (index == 0)
    {
        printf("不可改变头节点\n");
        return -1;
    }

    Node* p = H;
    
    for(int i = 0; i < index; i++)
        p = p->next;
    printf("replace:%d->%d\n", p->data, e);
    p->data = e;

    return 0;
}

// 查找指定元素
int search_index(Node* H, ELEM_TYPE e)
{
    Node* p = H;
    int index = 0;

    while (p != NULL || p->data != e)
    {
        p = p->next;
        index++;
    }

    if (p->data == e)
        return index;
    return -1;
}

int main()
{
    Node* C = init_list();
    insert_head(C, 1);
    insert_head(C, 2);
    insert_head(C, 3);
    show_list(C);
    insert_tail(C, 4);
    insert_tail(C, 5);
    insert_tail(C, 6);
    show_list(C);
    insert_index(C, 2, 7);
    show_list(C);
    printf("len:%d\n", len_list(C));
    delete_index(C, 2);
    replace_index(C, 3, 8);
    show_list(C);
    ELEM_TYPE res = search_index(C, 5);
    printf("res:%d\n", res);
    free_list(C);

    return 0;
}