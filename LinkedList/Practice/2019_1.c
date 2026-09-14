#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

/* 题目：设计尽可能高效的算法，查找链表中倒数第k个节点。成功输出data，返回1；否则返回0。 */

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

// 算法定义
// 双指针法
int search_k_double_pointer(Node* H, int k)
{
    Node* p_f = H->link;
    Node* p_s = H->link;
    int diff = 0;

    while (p_f != NULL && diff < k)
    {
        p_f = p_f->link;
        diff++;
    }

    if (diff < k) // 若元素不足k个则返回0
        return 0;
    
    while (p_f != NULL)
    {
        p_f = p_f->link;
        p_s = p_s->link;
    }

    printf("res:%d\n", p_s->data);
    return 1;
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

    int res = search_k_double_pointer(node, 7);
    
    return 0;
}