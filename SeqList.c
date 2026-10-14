#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define EXP_SIZE 10
typedef int ElemType; // 涉及printf均使用%d

// 顺序表
typedef struct{
    ElemType *data;
    int length;
    int max_length;
} SeqList;

/*
函数名称: init_list
输入: void
输出: SeqList* L
功能: malloc分配新顺序表指针
*/
SeqList* init_list()
{
    SeqList *L = (SeqList*)malloc(sizeof(SeqList));
    L->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    L->length = 0;
    L->max_length = MAX_SIZE;

    return L;
}

/*
函数名称: show_list
输入: SeqList* L
输出: int (status) 0/-1
功能: 打印顺序表内容，空指针提示并返回-1
*/
int show_list(SeqList *L)
{
    if (L->length == 0)
    {
        printf("表为空!\n");
        return -1;
    }

    for (int i = 0; i < L->length; i++)
        printf("%d ", L->data[i]);
    printf("\n");
    return 0;
}

/*
函数名称: merge_list
输入: SeqList* L1, SeqList* L2
输出: SeqList* L
功能: 返回新分配顺序表指针，内容为L1追加L2，失败返回NULL
*/
SeqList* merge_list(SeqList* L1, SeqList* L2)
{
    SeqList* L = init_list();
    L->max_length = L->length = L1->max_length + L2->max_length;
    ElemType* n = (ElemType*)realloc(L->data, L->max_length);

    if (!n)
    {
        printf("Allocate fail!\n");
        return NULL;
    }

    ElemType* p1r = L1->data[L1->length-1], *p2r = L2->data[L2->length-1];
    ElemType* p1 = L1->data, *p2 = L2->data, *p = L->data;
    
    while (p1 <= p1r)
        *p++ = *p1++;
    while (p2 <= p2r)
        *p++ = *p2++;

    return L;
}

/*
函数名称: append_list
输入: SeqList* L, ElemType e
输出: int (status) 0/-1
功能: 在顺序表末尾追加元素e，若表满提示并返回-1
*/
int append_list(SeqList *L, ElemType e)
{
    if (L->length >= MAX_SIZE)
    {
        printf("顺序表已满\n");
        return -1;
    }

    L->data[L->length] = e;
    L->length++;
    return 0;
}

/*
函数名称: append_list_exp
输入: SeqList* L, ElemType e
输出: int (status) 0/-1
功能: 在顺序表末尾追加元素e，若表满则尝试扩展长度，失败则提示表满并返回-1
*/
int append_list_exp(SeqList* L, ElemType e)
{
    if (L->length >= L->max_length)
    {
        ElemType* n = (ElemType*)realloc(L->data, (L->max_length + EXP_SIZE) * sizeof(ElemType));
        if (!n)
        {
            printf("Extend fail, list full!\n");
            return -1;
        }
        L->max_length += EXP_SIZE;
    }

    L->data[L->length] = e;
    L->length++;
    return 0;
}

/*
函数名称: insert_list
输入: SeqList* L, int pos, ElemType e
输出: int (status) 0/-1/-2
功能: 在顺序表指定个数位置pos插入元素e，失败、非法提示并返回-1/-2
*/
int insert_list(SeqList *L, int pos, ElemType e)
{
    int index = pos - 1;

    if (L->length >= MAX_SIZE)
    {
        printf("顺序表已满\n");
        return -1;
    }
    else if (index < 0 || index > L->length)
    {
        printf("插入位置不合法\n");
        return -2;
    }

    for (int i = L->length; i > index; i--)
        L->data[i] = L->data[i-1];
    L->data[index] = e;
    L->length++;

    return 0;
}

/*
函数名称: delete_list
输入: SeqList* L, int pos, ElemType *deleted
输出: int (status) 0/-1/-2
功能: 删除顺序表指定个数位置pos的元素，并赋值到deleted里，表空、非法提示并返回-1/-2
*/
int delete_list(SeqList *L, int pos, ElemType *deleted)
{
    int index = pos - 1;

    if (L->length == 0)
    {
        printf("表为空!\n");
        return -1;
    }
    else if (index < 0 || index >= L->length)
    {
        printf("删除位置不合法\n");
        return -2;
    }

    *deleted = L->data[index];
    for (int i = index; i < L->length - 1; i++)
        L->data[i] = L->data[i+1];
    L->length--;
    return 0;
}

/*
函数名称: replace_list
输入: SeqList* L, int pos, ElemType new, ElemType *pre
输出: int (status) 0/-1/-2
功能: 将顺序表指定个数位置pos元素赋值到pre，替换为new，表满、非法提示并返回-1/-2
*/
int replace_list(SeqList *L, int pos, ElemType new, ElemType *pre)
{
    int index = pos - 1;

    if (L->length == 0)
    {
        printf("表为空!\n");
        return -1;
    }
    else if (index < 0 || index >= L->length)
    {
        printf("替换位置不合法\n");
        return -2;
    }

    *pre = L->data[index];
    L->data[index] = new;
    return 0;
}

/*
函数名称: search_pos_list
输入: SeqList* L, ElemType e
输出: int pos
功能: 查找顺序表中第一个元素e，未找到返回0
*/
int search_pos_list(SeqList *L, ElemType e)
{
    for (int i = 0; i < L->length; i++)
        if (L->data[i] == e)
            return i + 1;
    return 0;
}

int main()
{
    SeqList* L = init_list();
    append_list(L, 10);
    append_list(L, 44);
    append_list(L, 62);
    append_list(L, 23);
    append_list(L, 37);
    show_list(L);
    insert_list(L, 2, 78);
    show_list(L);
    int deleted;
    delete_list(L, 3, &deleted);
    printf("delete: %d\n", deleted);
    show_list(L);
    int pre;
    replace_list(L, 4, 5, &pre);
    printf("replace: %d\n", pre);
    show_list(L);

    return 0;
}