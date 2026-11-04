#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 赫夫曼树
typedef struct HuffmanTreeNode{
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
} HTNode, *HTree;

typedef char **HuffmanCode;

/*
函数名称：HuffmanCoding
输入：HTree* HT, HuffmanCode* HC, int w[], int n
说明：根据给定的权重和叶节点个数建立赫夫曼树
*/
void HuffmanCoding(HTree* HT, HuffmanCode* HC, int w[], int n)
{
    HTree p;
    char* cd;
    int i;
    unsigned int c, f;

    if (n <= 1)
        return;

    int m = 2 * n - 1;
    *HT = (HTree)malloc((m + 1) * sizeof(HTNode));

    for (p = *HT + 1, i = 1; i <= m; i++, p++) // 初始化节点
    {
        p->weight = (i <= n) ? *(w++) : 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }

    unsigned int s1, s2, start;
    for (int k = n + 1; k <= m; k++) // 建立树
    {
        s1 = 0, s2 = 0;
        for (int j = 1; j <= k - 1; j++) // 选择最小结点
        {
            if ((*HT)[j].parent != 0)
                continue;

            if (s1 == 0 || (*HT)[j].weight < (*HT)[s1].weight)
            {
                s2 = s1;
                s1 = j;
            }
            else if (s2 == 0 || (*HT)[j].weight < (*HT)[s2].weight)
            {
                s2 = j;
            }
        }

        (*HT)[s1].parent = k;
        (*HT)[s2].parent = k;
        (*HT)[k].lchild = s1;
        (*HT)[k].rchild = s2;
        (*HT)[k].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }

    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
    cd = (char*)malloc(n * sizeof(char));
    cd[n-1] = '\0';

    for (int i = 1; i <= n; i++)
    {
        start = n - 1;
        for (c = i, f = (*HT)[c].parent; f != 0; c = f, f = (*HT)[f].parent)
            if ((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        (*HC)[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy((*HC)[i], &cd[start]);
        printf("%s\n", (*HC)[i]);
    }

    free(cd);
}
