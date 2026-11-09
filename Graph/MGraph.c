#include <stdio.h>
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

        while (getchar() != '\n')
            ;
        printf("Input arcs (v1 v2 w): \n");
        scanf("%c %c %d", &v1, &v2, &w);
        r = locate_vex_MG(G, v1);
        c = locate_vex_MG(G, v2);
        G->arcs[r][c] = w;
        if (type == 1)
            G->arcs[c][r] = w;
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

int main()
{
    pMG g = (pMG)malloc(sizeof(MGraph));

    create_MGraph(g);
    print_MGraph(g);

    return 0;
}