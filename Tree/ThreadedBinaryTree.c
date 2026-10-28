#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef char ElemType;

// 线索二叉树
typedef enum {Link, Thread} ThrTag;
typedef struct ThreadedTreeNode
{
    ElemType *data;
    ThrTag LTag;
    ThrTag RTag;
    ThreadedTreeNode *lchild;
    ThreadedTreeNode *rchild;
} ThreadedTreeNode, *TBTree;

/*
函数名称：trav_mid_TTree_1
输入：TBTree T
说明：中序遍历线索二叉树
*/
void trav_mid_TTree_1(TBTree T)
{
    TBTree p = T;
    
    while (p->LTag == Link) // 找首节点
        p = p->lchild;
    printf("%c ", p->data);

    while (p->rchild)
    {
        if (p->RTag == Link)
        {
            p = p->rchild;
            while (p->LTag == Link)
                p = p->lchild;
        }
        else
            p = p->rchild;
        printf("%c ", p->data);
    }
}

/*
函数名称：trav_mid_TTree_2
输入：TBTree T
说明：中序遍历线索二叉树
*/
void trav_mid_TTree_2(TBTree T)
{
    TBTree p = T;
    while (p)
    {
        while (p->LTag == Link)
            p = p->lchild;
        printf("%c ", p->data);
        while (p->RTag == Thread && p->rchild)
        {
            p = p->rchild;
            printf("%c ", p->data);
        }
        p = p->rchild;
    }
}

/*
函数名称：trav_pre_TTree
输入：TBTree T
说明：先序遍历线索二叉树
*/
void trav_pre_TTree(TBTree T)
{
    TBTree p = T;
    printf("%c ", p->data);
    while (p->rchild)
    {
        if (p->LTag == Link)
            p = p->lchild;
        else 
            p = p->rchild;
        printf("%c ", p->data);
    }
}

/*
函数名称：trav_post_stack_TTree
输入：TBTree T
说明：后序遍历线索二叉树（前序+栈逆序）
*/
void trav_post_stack_TTree(TBTree T)
{
    ElemType Stack[MAX_SIZE];
    int top = 0;
    
    TBTree p = T;
    Stack[top++] = p->data;
    while (p->rchild)
    {
        if (p->LTag == Link)
            p = p->lchild;
        else 
            p = p->rchild;
        Stack[top++] = p->data;
    }

    while (top)
        printf("%c ", Stack[--top]);
}

/*
函数名称：thrd_mid_TTree
输入：TBTree N
说明：中序线索化二叉树
*/
void thrd_mid_TTree(TBTree N)
{
    static TBTree pre_po = NULL;
    static TBTree pre_pr = NULL;

    if (N) // 后继
    {
        thrd_mid_TTree(N->lchild);
        if (!N->rchild)
            N->RTag = Thread;
        if (pre_po && pre_po->RTag == Thread)
            pre_po->rchild = N;
        pre_po = N;
        thrd_mid_TTree(N->rchild);
    }

    if (N) // 前驱
    {
        thrd_mid_TTree(N->lchild);
        if (!N->lchild)
        {
            N->LTag = Thread;
            N->lchild = pre_pr;
        }
        pre_pr = N;
        thrd_mid_TTree(N->rchild);
    }
}
