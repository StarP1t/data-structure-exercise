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
函数名称：free_ALGraph
输出：void
说明：释放邻接表图所有弧结点
*/
void free_ALGraph(ALGraph *G)
{
    for (int i = 0; i < G->vexnum; i++)
    {
        ArcNode* p = G->vertices[i].firstarc, *next = NULL;

        while (p)
        {
            next = p->nextarc;
            free(p);
            p = next;
        }

        G->vertices[i].firstarc = NULL;
    }
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

/*
函数名称：top_logical_sort_dALG
输入：const pALG G
输出：int (status) 0/1/2
说明：拓扑排序有向图
*/
int top_logical_sort_dALG(const pALG G)
{
    int* indegree = (int*)calloc(G->vexnum, sizeof(int));
    if (indegree == NULL)
    {
        printf("内存分配失败\n!");
        return 2;
    }

    // 初始化各点入度
    for (int i = 0; i < G->vexnum; i++)
    {
        ArcNode* p = G->vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    
    int top = -1;

    // 入度为0顶点入栈
    for (int i = 0; i < G->vexnum; i++)
        if (indegree[i] == 0)
        {
            indegree[i] = top;
            top = i;
        }

    int count = 0;

    while (top != -1)
    {
        // 出栈
        int i = top;
        top = indegree[top];
        printf("%c ", G->vertices[i].data);
        count++;

        for (ArcNode *p = G->vertices[i].firstarc; p != NULL; p = p->nextarc)
        {
            int adj = p->adjvex;

            indegree[adj]--;
            if (indegree[adj] == 0) // 入栈
            {
                indegree[adj] = top;
                top = adj;
            }
        }
    }
    putchar('\n');

    free(indegree);

    if (count < G->vexnum)
    {
        printf("图有环!\n");
        return 1;
    }
    else
        return 0;
}

/*
函数名称：top_logical_sort_rev_dALG
输入：const pALG G
输出：int (status) 0/1/2
说明：逆拓扑排序有向图 TODO 更改遍历结构
*/
int top_logical_sort_rev_dALG(const pALG G)
{
    int* outdegree = (int*)calloc(G->vexnum, sizeof(int));
    int* printed = (int*)calloc(G->vexnum, sizeof(int));
    if (outdegree == NULL || printed == NULL)
    {
        printf("内存分配失败\n!");
        return 2;
    }

    // 初始化各点出度
    for (int i = 0; i < G->vexnum; i++)
    {
        ArcNode* p = G->vertices[i].firstarc;
        
        while (p)
        {
            outdegree[i]++;
            p = p->nextarc;
        }
    }
    
    int top = -1;

    // 出度为0顶点入栈
    for (int i = 0; i < G->vexnum; i++)
        if (outdegree[i] == 0)
        {
            outdegree[i] = top;
            top = i;
        }

    int count = 0;

    while (top != -1)
    {
        // 出栈
        int i = top;
        top = outdegree[top];
        printf("%c ", G->vertices[i].data);
        printed[i] = 1;
        count++;

        for (int j = 0; j < G->vexnum; j++)
        {
            if (printed[j])
                continue;

            ArcNode* p = G->vertices[j].firstarc;
            while (p)
            {
                if (p->adjvex == i)
                    outdegree[j]--;

                p = p->nextarc;
            }

            if (outdegree[j] == 0) // 入栈
            {
                outdegree[j] = top;
                top = j;
            }
        }
    }
    putchar('\n');

    free(outdegree);
    free(printed);

    if (count < G->vexnum)
    {
        printf("图有环!\n");
        return 1;
    }
    else
        return 0;
}

/*
函数名称：top_logical_order_dALG
输入：const pALG G, int* T, int* ptopT, int* ve
输出：int (status) 0/-1
说明：拓扑排序计算关键路径最早用时
*/
int top_logical_order_dALG(const pALG G, int* T, int* ptopT, int* ve)
{
    int* indeg = (int*)calloc(G->vexnum, sizeof(int));
    int* S = (int*)calloc(G->vexnum, sizeof(int));
    if (indeg == NULL || S == NULL)
    {
        printf("内存分配失败\n!");
        return 2;
    }

    // 初始化各点入度
    for (int i = 0; i < G->vexnum; i++)
    {
        ArcNode* p = G->vertices[i].firstarc;
        while (p)
        {
            indeg[p->adjvex]++;
            p = p->nextarc;
        }
    }

    // 初始化ve表
    for (int i = 0; i < G->vexnum; i++)
        ve[i] = 0;

    int topS = -1;

    // 入度为0顶点入栈
    for (int i = 0; i < G->vexnum; i++)
        if (indeg[i] == 0)
            S[++topS] = i;

    int count = 0;
    int topT = *ptopT;

    while (topS != -1)
    {
        int j = S[topS--];
        T[++topT] = j;
        count++;

        // 更新ve表
        for (ArcNode* p = G->vertices[j].firstarc; p != NULL; p = p->nextarc)
        {
            int k = p->adjvex;

            if (--indeg[k] == 0)
                S[++topS] = k;

            ve[k] = (ve[j] + p->info > ve[k]) ? (ve[j] + p->info) : ve[k];
        }
    }

    free(indeg);
    free(S);

    if (count < G->vexnum)
    {
        printf("图有环，建立失败！\n");
        return -1;
    }
    else
        return 0;
}

/*
函数名称：critical_path_dALG
输入：const pALG G
输出：int (status) 0/-1
说明：寻找邻接表图的关键事件并输出
*/
int critical_path_dALG(const pALG G)
{
    int* T = (int*)calloc(G->vexnum, sizeof(int));
    int* ve = (int*)calloc(G->vexnum, sizeof(int));
    int* vl = (int*)calloc(G->vexnum, sizeof(int));
    if (T == NULL || ve == NULL || vl == NULL)
    {
        printf("内存分配失败！\n");
        return -1;
    }

    int topT = -1;

    if (top_logical_order_dALG(G, T, &topT, ve))
    {
        free(T);
        free(ve);
        free(vl);
        return -1;
    }

    // 初始化vl表
    int maxe = 0;
    for (int i = 0; i < G->vexnum; i++)
        maxe = (maxe >= ve[i]) ? maxe : ve[i];
    for (int i = 0; i < G->vexnum; i++)
        vl[i] = maxe;

    // 计算更新vl表
    while (topT != -1)
    {
        int cur = T[topT--];

        for (ArcNode* p = G->vertices[cur].firstarc; p != NULL; p++)
        {
            int adj = p->adjvex, t = p->info;
            vl[cur] = (vl[cur] <= vl[adj] - t) ? vl[cur] : vl[adj] - t;
        }
    }

    // 查找关键事件
    printf("===============================\n");
    printf("tail head time  ve  vl critical\n");
    for (int cur = 0; cur < G->vexnum; cur++)
        for (ArcNode* p = G->vertices[cur].firstarc; p != NULL; p = p->nextarc)
        {
            int e = ve[cur], l = vl[p->adjvex] - p->info;
            char tag = (e == l) ? '*' : ' ';

            printf("%4d %4d %4d %3d %3d %4c\n", cur, p->adjvex, p->info, e, l, tag);
        }
    printf("===============================\n");

    free(T);
    free(ve);
    free(vl);
    return 0;
}

int main()
{
    ALGraph G;

    create_ALGraph(&G);
    DFSTrav(&G);
    BFSTrav(&G);
    
    if (!top_logical_sort_dALG(&G))
        top_logical_sort_rev_dALG(&G);

    critical_path_dALG(&G);

    free_ALGraph(&G);
    return 0;
}
