#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20

// 图
typedef enum {DG, DN, UDG, UDN} GType;
typedef int AdjMat[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef char VexType;

// 图（数组法）
typedef struct 
{
    VexType Vexs[MAX_VERTEX_NUM];
    AdjMat arcs;
    int vexnum, arcnum;
} MGraph, *pMG;

/*
函数名称：locate_vex_MG
输入：const MGraph *G, VexType val
输出：int index
说明：查找数组法图的点，失败返回-1
*/
int locate_vex_MG(const MGraph *G, VexType val)
{
    for (int i = 0; i < G->vexnum; i++)
        if (G->Vexs[i] == val)
            return i;

    printf("Error val!\n");
    return -1;
}

/*
函数名称：create_MGraph
输入：MGraph* G
说明：TODO 错误检查；创建一个有向/无向数组图
*/
void create_MGraph(MGraph* G)
{
    int type;
    printf("Graph type (0:DG, 1:UDG): ");
    scanf("%d", &type);

    printf("Input vexnum and arcnum: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    printf("Input Vertices: ");
    scanf("%s", G->Vexs);

    for (int i = 0; i < G->vexnum; i++)
        for (int j = 0; j < G->vexnum; j++)
            G->arcs[i][j] = 0;

    for (int i = 0; i < G->arcnum; i++)
    {
        int r, c;
        char v1, v2;
        int w;

        while (1)
        {
            while (getchar() != '\n')
                ;
            printf("Input arcs (v1 v2 w): \n");
            scanf("%c %c %d", &v1, &v2, &w);
            r = locate_vex_MG(G, v1);
            c = locate_vex_MG(G, v2);
            if (G->arcs[r][c] == 0)
            {
                G->arcs[r][c] = w;
                if (type == 1)
                    G->arcs[c][r] = w;
                break;
            }
            else
                printf("Arc has been set!\n");
        }
    }
}

/*
函数名称：print_MGraph
输入：const MGraph* G
说明：打印数组图节点及关系矩阵
*/
void print_MGraph(const MGraph* G)
{
    printf("Output Vertices: ");
    printf("%s\n", G->Vexs);
    printf("Output AdjMatrix:\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
            printf("%4d", G->arcs[i][j]);
        putchar('\n');
    }
}

// 普里姆算法辅助结构定义
#define INFINITY 2147483647
typedef int VRType;
struct 
{
    VexType adjvex;
    VRType lowcost;
} closedge[MAX_VERTEX_NUM];

/*
函数名称：MST_Prim_MGraph
输入：const MGraph* G, const VexType start
说明：普利姆算法，打印最小生成树的边
*/
void MST_Prim_MGraph(const MGraph* G, const VexType start)
{
    // 起始点下标确定
    int k = locate_vex_MG(G, start);
    if (k == -1)
    {
        printf("Invalid start node!\n");
        return;
    }

    // 初始化辅助数组
    for (int i = 0; i < G->vexnum; i++) 
    {
        if (i != k)
        {
            closedge[i].adjvex = start;
            closedge[i].lowcost = (G->arcs[k][i] == 0) ? INFINITY : G->arcs[k][i];
        }
    }
    closedge[k].lowcost = 0;

    for (int i = 1; i < G->vexnum; i++) // 循环直到所有点都加入集合
    {
        int mincost = INFINITY;
        
        for (int j = 0; j < G->vexnum; j++) // 寻找当前辅助数组权最小边
        {
            if (closedge[j].lowcost < mincost && closedge[j].lowcost != 0)
            {
                mincost = closedge[j].lowcost;
                k = j;
            }
        }

        printf("(%c, %c)\n", closedge[k].adjvex, G->Vexs[k]);
        closedge[k].lowcost = 0;

        // 更新辅助数组
        for (int j = 0; j < G->vexnum; j++)
        {
            if (G->arcs[k][j] < closedge[j].lowcost && G->arcs[k][j] != 0)
            {
                closedge[j].adjvex = G->Vexs[k];
                closedge[j].lowcost = G->arcs[k][j];
            }
        }
    }
}

int main()
{
    pMG g = (pMG)malloc(sizeof(MGraph));

    create_MGraph(g);
    print_MGraph(g);
    MST_Prim_MGraph(g, 'a');

    return 0;
}