#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20

// 邻接表图
typedef char VexType; 
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode* nextarc;
    int info;
} ArcNode; // 邻接表边节点

typedef struct VNode
{
    VexType data;
    ArcNode* firstarc;
} VNode, AdjList[MAX_VERTEX_NUM]; // 表头接点

typedef struct 
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph, *pALG; // 邻接表图

/*
函数名称：create_ArcNode
输出：ArcNode* newnode
说明：初始化一个新边节点
*/
ArcNode* create_ArcNode()
{
    ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = -1;
    p->nextarc = NULL;
    p->info = 0;

    return p;
}

/*
函数名称：locate_vex_ALG
输入：const ALGraph *G, VexType val
输出：int index
说明：查找邻接表法图的点，失败返回-1
*/
int locate_vex_ALG(const ALGraph *G, VexType val)
{
    for (int i = 0; i < G->vexnum; i++)
        if (G->vertices[i].data == val)
            return i;

    printf("Error val!\n");
    return -1;
}

/*
函数名称：create_ALGraph
输入：ALGraph* G
说明：TODO 错误检查；创建一个邻接表有向/无向图
*/
void create_ALGraph(ALGraph* G)
{
    int type;
    printf("Graph type (0:DG, 1:UDG): ");
    scanf("%d", &type);

    printf("Input vexnum and arcnum: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    while (getchar() != '\n')
            ;
    printf("Input Vertices: ");
    for (int i = 0; i < G->vexnum; i++)
    {
        scanf("%c", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }

    printf("Input arcs (v1 v2 w): \n");
    for (int i = 0; i < G->arcnum; i++)
    {
        int r, c;
        char v1, v2;
        int w;

        while (getchar() != '\n')
            ;
        scanf("%c %c %d", &v1, &v2, &w);
        r = locate_vex_ALG(G, v1);
        c = locate_vex_ALG(G, v2);

        ArcNode* newnode = create_ArcNode();
        newnode->adjvex = c;
        newnode->info = w;
        newnode->nextarc = G->vertices[r].firstarc; // 头插法
        G->vertices[r].firstarc = newnode;
        if (type == 1)
        {
            ArcNode* newnode = create_ArcNode();
            newnode->adjvex = r;
            newnode->info = w;
            newnode->nextarc = G->vertices[c].firstarc;
            G->vertices[c].firstarc = newnode;
        }
    }
}
