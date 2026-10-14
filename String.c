#include <stdio.h>
#include <stdlib.h>

// 串
typedef struct
{
    char *data;
    int length;
    int max_len;
}String;

// 动态初始化
String* init_str(int len)
{
    String* s = (String*)malloc(sizeof(String));
    s->data = (char*)malloc(sizeof(char) * len);
    s->length = 0;
    s->max_len = len;

    return s;
}

// 释放串
void free_str(String* s)
{
    free(s->data);
    free(s);
}

// 获取长度
int len_string(String* s)
{
    return s->length;
}

// 串赋值
int assign_str(String* s, char* chars)
{
    if (chars == NULL)
    {
        s->length = 0;
        return -1;
    }

    int i = 0;
    while (chars[i] != '\0')
    {
        s->data[i] = chars[i];
        i++;
    }
    s->length = i;

    return 0;
}

// 串比较
int compare_str(String* s1, String* s2)
{
    if (s1 == NULL)
    {
        printf("s1 is nullptr!\n");
        return -1;
    }
    else if (s2 == NULL)
    {
        printf("s2 is nullptr!\n");
        return 1;
    }

    if (s1->length != s2->length)
        return s1->length - s2->length;
    
    for (int i = 0; i < s1->length; i++)
    {
        if (s1->data[i] != s2->data[i])
            return s1->data[i] - s2->data[i];
    }
    return 0;
}

/*
函数名称：串追加
输入: String* 目标串, String* 追加串
输出: int 状态 (正常: 0/空串: -1/追加溢出: 1)
*/
int cat_str(String* dest, String* srcs)
{
    if (dest == NULL | srcs == NULL)
        return -1;
    
    int d_i = dest->length, s_i = 0;
    while (d_i < dest->max_len && s_i < srcs->length)
    {
        dest->data[d_i] = srcs->data[s_i];
        s_i++;
        d_i++;
    }
    dest->length = d_i;
    
    if (s_i == srcs->length)
        return 0;
    else
        return 1;
}

/*
函数名称：串插入
输入: String* 目标串, String* 插入串, int 插入位置下标
输出: String* 结果串 (失败：NULL) 
*/
String* insert_str(String* dest, String* srcs, int index)
{
    if (dest == NULL || srcs == NULL)
        return NULL;
    else if (index < 0 || index > dest->length)
        return NULL;
    
    int new_max_len = dest->length + srcs->length;
    String* tmp = init_str(new_max_len);
    if (tmp == NULL)
        return NULL;

    for (int i = 0; i < index; i++)
        tmp->data[tmp->length++] = dest->data[i];
    for (int i = 0; i < srcs->length; i++)
        tmp->data[tmp->length++] = srcs->data[i];   
    for (int i = index; i < dest->length; i++)
        tmp->data[tmp->length++] = dest->data[i];
    
    return tmp;
}
