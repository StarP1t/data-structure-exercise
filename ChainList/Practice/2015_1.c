#include <stdio.h>
#include <stdlib.h>
#define ELEM_TYPE int

/* 题目：设计尽可能时间高效的算法，在保存了n个num的单向链表中，
   查找并删除绝对值（小于n）的相同元素，仅保留第一次出现的元素。 */

// 基础定义
// 单向链表定义
typedef struct Node
{
    ELEM_TYPE data;
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
void insert_tail(Node* H, ELEM_TYPE e)
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
// 数组保存法
void find_delete_same_abs_val(Node* H, int n)
{
    Node* now = H->link;
    Node* pre = H;
    int* count = (int*)calloc(n + 1, sizeof(int));

    while (now != NULL)
    {
        int num = abs(now->data);

        if (count[num])
        {
            pre->link = now->link;
            free(now);
            now = pre->link;
            continue;
        }
        count[num] = 1;

        now = now->link;
        pre = pre->link;
    }

    free(count);
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
    insert_tail(node, -4);
    insert_tail(node, 2);
    insert_tail(node, -1);
    show_list(node);

    find_delete_same_abs_val(node, 6);
    show_list(node);
    
    return 0;
}