#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

// 链式二叉树
typedef struct TreeNode
{
    ElemType data;
    TreeNode* lchild;
    TreeNode* rchild;
} TreeNode, *BTree;

/*
函数名称: init_tree
输出: BTree t
说明: 动态分配一个新二叉树的根节点并返回
*/
BTree init_tree()
{
    BTree t = (BTree)malloc(sizeof(TreeNode));
    t->data = NULL;
    t->lchild = NULL;
    t->rchild = NULL;

    return t;
}

/*
函数名称: free_tree
输入: BTree t
说明: 按后序遍历的顺序释放二叉树
*/
void free_tree(BTree t)
{
    if (t == NULL)
        return;
    
    free_tree(t->lchild);
    free_tree(t->rchild);
    if (t->lchild != NULL)
        free(t->lchild);
    if (t->rchild != NULL)
        free(t->rchild);

    free(t);
}

/*
函数名称: trav_pre_tree
输入: BTree t
说明: 前序遍历二叉树 
*/
void trav_pre_tree(BTree t)
{
    if (t == NULL)
        return;

    printf("%c ", t->data);
    trav_pre_tree(t->lchild);
    trav_pre_tree(t->rchild);
}

/*
函数名称: trav_mid_tree
输入: BTree t
说明: 中序遍历二叉树 
*/
void trav_mid_tree(BTree t)
{
    if (t == NULL)
        return;

    trav_pre_tree(t->lchild);
    printf("%c ", t->data);
    trav_pre_tree(t->rchild);
}

/*
函数名称: trav_post_tree
输入: BTree t
说明: 后序遍历二叉树 
*/
void trav_post_tree(BTree t)
{
    if (t == NULL)
        return;

    trav_pre_tree(t->lchild);
    trav_pre_tree(t->rchild);
    printf("%c ", t->data);
}
