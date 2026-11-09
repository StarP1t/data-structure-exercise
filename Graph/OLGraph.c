#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20

// 十字链表图
typedef char VexType;
typedef struct ArcBox
{
    int tvex;
    int hvex;
    struct ArcBox* hlink;
    struct ArcBox* tlink;
    int info;
} ArcBox; // 链表节点

typedef struct VexNode
{
    VexType data;
    ArcBox* infirst, outfirst;
} VexNode; // 十字链表头

typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum; 
} OLGraph, *pOLG; // 十字链表图
