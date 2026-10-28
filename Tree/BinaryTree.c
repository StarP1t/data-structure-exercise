#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef char ElemType;
typedef TreeNode* ElemType_s;

// 链式二叉树
typedef struct TreeNode
{
    ElemType data;
    TreeNode* lchild;
    TreeNode* rchild;
} TreeNode, *BTree;

// 栈
typedef struct
{
    ElemType_s* data;
    int top;
} Stack;

/*
函数名称: init_stack
输出: Stack* s
说明: 动态分配初始化新栈，返回栈指针
*/
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType_s*)malloc(sizeof(ElemType_s) * MAX_SIZE);
    s->top = -1;
    return s;
}

/*
函数名称: free_stack
输入: Stack* s
说明: 释放栈内数据和栈
*/
void free_stack(Stack* s)
{
    free(s->data);
    free(s);
}

/*
函数名称: is_empty_stack
输入: Stack *s
输出: int 1/0 
说明: 判断是否栈空，是则输出1，否则0
*/
int is_empty_stack(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

/*
函数名称: push
输入: Stack* s, ElemType_s e
输出: int (status) -1/0
说明: 将元素e压入栈s，若栈满提示并输出-1
*/
int push(Stack* s, ElemType_s e)
{
    if (s->top >= MAX_SIZE - 1)
    {
        printf("Stack full!\n");
        return -1;
    }

    s->data[++s->top] = e;
    return 0;
}

/*
函数名称: pop
输入: Stack* s, ElemType_s *e
输出: int (status) -1/0
说明: 将栈顶元素赋值到元素指针内存并出栈，若栈空提示并输出-1
*/
int pop(Stack* s, ElemType_s *e)
{
    if (s->top == -1)
    {
        printf("Stack empty!\n");
        return -1;
    }

    *e = s->data[s->top--];
    return 0;
}

/*
函数名称: get_top
输入: Stack* s
输出: ElemType e
说明: 将栈顶元素返回，若栈空提示并输出NULL
*/
ElemType get_top(Stack* s)
{
    if (s->top == -1)
    {
        printf("Stack empty!\n");
        return NULL;
    }
    return s->data[s->top];
}

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
函数名称: trav_pre_iter_tree
输入: BTree t
说明: 前序遍历二叉树 
*/
void trav_pre_iter_tree(BTree t)
{
    if (t == NULL)
        return;

    printf("%c ", t->data);
    trav_pre_tree(t->lchild);
    trav_pre_tree(t->rchild);
}

/*
函数名称: trav_mid_iter_tree
输入: BTree t
说明: 中序遍历二叉树 
*/
void trav_mid_iter_tree(BTree t)
{
    if (t == NULL)
        return;

    trav_pre_tree(t->lchild);
    printf("%c ", t->data);
    trav_pre_tree(t->rchild);
}

/*
函数名称: trav_post_iter_tree
输入: BTree t
说明: 后序遍历二叉树 
*/
void trav_post_iter_tree(BTree t)
{
    if (t == NULL)
        return;

    trav_pre_tree(t->lchild);
    trav_pre_tree(t->rchild);
    printf("%c ", t->data);
}

/*
函数名称: trav_pre_stack_tree_1
输入: BTree t
说明: 非递归栈前序遍历二叉树
*/
void trav_pre_stack_tree_1(BTree t)
{
    Stack* s = init_stack();
    BTree p = t;

    push(s, NULL);
    while (p)
    {
        printf("%c ", t->data);
        if (t->rchild)
            push(s, t->rchild);
        if (t->lchild)
            t = t->lchild;
        else
            pop(s, &t);
    }
    
    free_stack(s);
}

/*
函数名称: trav_pre_stack_tree_2
输入: BTree t
说明: 非递归数组栈前序遍历二叉树
*/
void trav_pre_stack_tree_2(BTree t)
{
    BTree stack[MAX_SIZE];
    int top = 0;
    BTree p;

    do
    {
        while (p)
        {
            printf("%c ", p->data);
            stack[top++] = p;
            p = p->lchild;
        }

        if (top)
        {
            p = stack[top--];
            p = p->rchild;
        } 
    } while (p || top);
}

/*
函数名称: trav_mid_stack_tree_1
输入: BTree t
说明: 非递归栈中序遍历二叉树
*/
void trav_mid_stack_tree_1(BTree t)
{
    Stack* s = init_stack();
    BTree p = t;

    do
    {
        while (p)
        {
            push(s, p);
            p = p->lchild;
        }

        if (get_top(s) != t)
        {
            pop(s, &p);
            printf("%c ", p);
            p = p->rchild;
        }
    } while (p || (get_top(s) != t));
    
    free_stack(s);
}

/*
函数名称: trav_mid_stack_tree_2
输入: BTree t
说明: 非递归栈中序遍历二叉树
*/
void trav_mid_stack_tree_2(BTree t)
{
    Stack* s = init_stack();
    BTree p = t;

    while (p || !is_empty_stack(s))
        if (p)
        {
            push(s, p);
            p = p->lchild;
        }
        else
        {
            pop(s, &p);
            printf("%c ", p->data);
            p = p->rchild;
        }

    free_stack(s);
}

/*
函数名称: trav_post_stack_tree_1
输入: BTree t
说明: 非递归栈后序遍历二叉树
*/
void trav_post_stack_tree_1(BTree t)
{
    Stack* s = init_stack();
    BTree p = t, l = NULL;

    while (!is_empty_stack(s))
        if (p && p != l)
        {
            push(s, p);
            p = p->lchild;
        }
        else
        {
            pop(s, &p);
            if (p->rchild && p->rchild != l)
            {
                push(s, p);
                p = p->rchild;
            }
            else
            {
                printf("%c ", p->data);
                l = p;
            }
        }
}

/*
函数名称: create_prev_iter_tree
输入: BTree root
输出: int (status) 0
说明: 前序递归创建二叉树，输入空格为空结点
*/
int create_prev_iter_tree(BTree root)
{
    char ch;
    scanf("%c", &ch);

    if (ch == ' ')
        root = NULL;
    else
    {
        root = init_tree();
        root->data = ch;
        create_prev_iter_tree(root->lchild);
        create_prev_iter_tree(root->rchild);
    }
    return 0;
}

/*
函数名称: dep_tree
输入: BTree t
输出: int depth
说明: 递归计算树深度
*/
int depth_tree(BTree t)
{
    int depl, depr;

    if (t)
    {
        depl = depth_tree(t->lchild);
        depr = depth_tree(t->rchild);

        return depl >= depr ? depl + 1 : depr + 1;
    }

    return 0;
}

/*
函数名称: size_tree
输入: BTree t
输出: int size
说明: 递归计算树总结点数
*/
int size_tree(BTree t)
{
    if (t)
        return 1 + size_tree(t->lchild) + size_tree(t->rchild);
    else
        return 0;
}
