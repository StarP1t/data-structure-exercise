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

// 动态初始化
SeqList* init_list()
{
    SeqList *L = (SeqList*)malloc(sizeof(SeqList));
    L->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    L->length = 0;
    L->max_length = MAX_SIZE;

    return L;
}

// 遍历
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

// 合并
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

// 末尾添加
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

// 末尾添加-扩展表
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

// 指定位置插入
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
        return -1;
    }

    for (int i = L->length; i > index; i--)
        L->data[i] = L->data[i-1];
    L->data[index] = e;
    L->length++;

    return 0;
}

// 指定删除
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
        return -1;
    }

    *deleted = L->data[index];
    for (int i = index; i < L->length - 1; i++)
        L->data[i] = L->data[i+1];
    L->length--;
    return 0;
}

// 指定替换
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
        return -1;
    }

    *pre = L->data[index];
    L->data[index] = new;
    return 0;
}

// 搜索（1开始顺序）
int searchpos_list(SeqList *L, ElemType e)
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