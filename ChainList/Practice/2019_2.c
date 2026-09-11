#include <stdio.h>
#include <stdlib.h>
#define ELEM_TYPE int

/* 题目：将一个链表a1a2a3...an改变为a1ana2an-1a3...顺序 */

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

// 反转链表（len>3）
Node* reverse_list(Node* H)
{
    Node* p1 = NULL;
    Node* p2 = H->next;
    Node* p3;

    while (p2 != NULL)
    {
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    p2 = init_list();
    p2->next = p1;

    return p2;
}

// 实现算法 
Node* change_list(Node* H)
{
    Node* pf = H->next;
    Node* ps = H;

    while (pf != NULL && pf->next != NULL)
    {
        pf = pf->next->next;
        ps = ps->next;
    }

    
    ps = reverse_list(ps);
    ps = ps->next;
    pf = H->next;
    Node* pfa = pf->next;
    Node* psa = ps->next;

    while (pfa != NULL && psa != NULL)
    {
        pf->next = ps;
        ps->next = pfa;
        pf = pfa;
        ps = psa;
        pfa = pfa->next;
        psa = psa->next;
    }

    if (psa != NULL)
        pf->next = ps;

    return H;
}

// 测试
int main()
{
    Node* node = init_list();

    insert_tail(node, 1);
    insert_tail(node, 2);
    insert_tail(node, 3);
    insert_tail(node, 4);
    insert_tail(node, 5);
    insert_tail(node, 6);
    insert_tail(node, 7);
    show_list(node);

    change_list(node);
    show_list(node);
    
    return 0;
}