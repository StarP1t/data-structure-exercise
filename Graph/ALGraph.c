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

/*
函数名称：DFS
输入：const ALGraph* G, int v, int* visited[MAX_VERTEX_NUM]
输出：void
说明：深度优先递归遍历图
*/
void DFS(const ALGraph* G, int v, int visited[MAX_VERTEX_NUM])
{
    const ALGraph g = *G;
    const ArcNode* p;
    printf("%c ", g.vertices[v].data);
    visited[v] = 1;
    p = g.vertices[v].firstarc;

    while (p)
    {
        if (!visited[p->adjvex])
            DFS(G, p->adjvex, visited);
        p = p->nextarc;
    }
}

/*
函数名称：DFSTrav
输入：const pALG G
输出：void
说明：深度优先遍历图调用
*/
void DFSTrav(const pALG G)
{
    int visited[MAX_VERTEX_NUM] = {0};

    for (int v = 0; v < G->vexnum; v++)
        if (!visited[v])
            DFS(G, v, visited);
    putchar('\n');
}

/*
函数名称：BFS
输入：const ALGraph* G, int v, int visited[MAX_VERTEX_NUM]
输出：void
说明：广度优先遍历图
*/
void BFS(const ALGraph* G, int v, int visited[MAX_VERTEX_NUM])
{
    const ALGraph g = *G;
    const ArcNode *p;
    int Queue[MAX_VERTEX_NUM] = {0};
    int front = 0, tail = 0;

    printf("%c ", g.vertices[v].data);

    visited[v] = 1;
    Queue[tail++] = v;

    while (front != tail)
    {
        v = Queue[front++];
        p = g.vertices[v].firstarc;
        
        while (p)
        {
            if (!visited[p->adjvex])
            {
                printf("%c ", G->vertices[p->adjvex].data);
                visited[p->adjvex] = 1;
                Queue[tail++] = p->adjvex;
            }
            
            p = p->nextarc;
        }
    }
}

/*
函数名称：BFSTrav
输入：const pALG G
输出：void
说明：广度优先遍历图调用
*/
void BFSTrav(const pALG G)
{
    int visited[MAX_VERTEX_NUM] = {0};

    for (int v = 0; v < G->vexnum; v++)
        if (!visited[v])
            BFS(G, v, visited);
    putchar('\n');
}

int main()
{
    ALGraph G;

    create_ALGraph(&G);
    DFSTrav(&G);
    BFSTrav(&G);

    return 0;
}
