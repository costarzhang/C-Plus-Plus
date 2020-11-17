#include <iostream>
#include <float.h>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

// 图的邻接矩阵存储
typedef struct VertexType
{
    int n;       // 结点编号
    string info; // 结点信息
} VertexType;

typedef struct MGraph
{
    float **edges;
    int v, e;        // 结点数量和边的数量
    VertexType *vex; // 结点信息
} MGraph;

MGraph initMGraph(int v, int e)
{
    MGraph mgraph;
    mgraph.v = v;
    mgraph.e = e;

    // 二维邻接矩阵初始化
    mgraph.edges = new float *[v];
    for (int i = 0; i < v; i++)
    {
        mgraph.edges[i] = new float[v];
    }

    // 邻接矩阵初始化
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i != j)
            {
                mgraph.edges[i][j] = DBL_MAX;
            }
            else
            {
                mgraph.edges[i][j] = 0; // 结点自己到自己的距离规定为0
            }
        }
    }

    mgraph.vex = new VertexType[v];
    for (int i = 0; i < v; i++)
    {
        mgraph.vex[i].n = i;
    }
    return mgraph;
}

// 向图中添加边
void addedge(MGraph mgraph, int src, int dest, float weight)
{

    mgraph.edges[src][dest] = weight;
}

// 打印邻接矩阵
void printgraph(MGraph mgraph)
{
    cout << "*"
         << "  ";
    for (int k = 0; k < mgraph.v; k++)
    {
        cout << setiosflags(ios::left) << setw(5) << k << "  ";
    }
    cout << endl;
    for (int i = 0; i < mgraph.v; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < mgraph.v; j++)
        {
            if (mgraph.edges[i][j] < DBL_MAX)
            {
                cout << setiosflags(ios::left) << setw(5) << mgraph.edges[i][j] << "  ";
            }
            else
            {
                cout << setiosflags(ios::left) << setw(5) << "+"
                     << "  ";
            }
        }
        cout << endl;
    }
}

void printlowcost(float l[], int v)
{
    for (int i = 0; i < v; i++)
    {
        if (l[i] < DBL_MAX)
        {
            cout << setiosflags(ios::left) << setw(5) << l[i] << "  ";
        }
        else
        {
            cout << setiosflags(ios::left) << setw(5) << "+"
                 << "  ";
        }
    }
    cout << endl;
}

// 最小生成树
void prim(MGraph mgraph, int v0, int &sum)
{
    float *lowcost = new float[mgraph.v]; // 记录当前生成树到剩余各顶点的最短边权值，如lowcost[j], 表示当前生成树到顶点j的最短边权值
    int *src = new int[mgraph.v];         // 记录新加入的边的信息，src[i] = j,表示边i----j
    int *vest = new int[mgraph.v];        // 标志结点是否已经加入生成树
    float min;
    int i, j;
    int v = v0;
    int k;
    for (i = 0; i < mgraph.v; i++)
    {
        src[i] = v0;
    }
    // 此时生成树中只有一个结点,生成树到各结点的最短边权值
    // 即为该结点到图中其余各结点的边的权值
    for (i = 0; i < mgraph.v; i++)
    {
        lowcost[i] = mgraph.edges[v0][i];
        vest[i] = 0;
    }
    // 将v0并入树中
    vest[v0] = 1;
    sum = 0;

    // 检查图中剩余结点
    for (i = 0; i < mgraph.v - 1; i++)
    {
        min = DBL_MAX;
        // 选择最小候选边
        for (j = 0; j < mgraph.v; j++)
        {
            if (vest[j] == 0 && lowcost[j] < min)
            { // 选出当前生成树到其余结点最短边中最短的一条
                min = lowcost[j];
                k = j; // 记录新加入的结点
            }
        }
        // 将新结点并入生成树
        vest[k] = 1;
        v = k;
        cout << src[k] << " --" << min << "-- " << k << endl;
        // 记录最小生成树的权值
        sum += min;
        // 更新当前生成树到剩余结点的候选边的权值
        for (j = 0; j < mgraph.v; j++)
        {
            if (vest[j] == 0 && mgraph.edges[v][j] < lowcost[j])
            {
                lowcost[j] = mgraph.edges[v][j];
                src[j] = v;
            }
        }
    }
}

// 最小生成树,kruskal
typedef struct Road
{
    int a, b;     // 一条边的两端
    float weight; // 权值
} Road;
// 寻找
int getroot(int a, int v[])
{
    while (a != v[a])
    { // 向父节点回溯寻找根结点
        a = v[a];
    }
    return a;
}
void kruskal(MGraph mgraph, int &sum, int v[])
{
    Road road[mgraph.e]; // 存储图中的边
    int edges = 0;
    int i, j;
    for (i = 0; i < mgraph.v; i++)
    {
        for (j = 0; j < mgraph.v; j++)
        {
            if (mgraph.edges[i][j] != 0 && mgraph.edges[i][j] < DBL_MAX)
            {
                road[edges].a = i; // 和一条边相关联的两个顶点
                road[edges].b = j;
                road[edges].weight = mgraph.edges[i][j];
                cout << road[edges].a << "   " << road[edges].weight << " " << road[edges].b << endl;
                edges++;
            }
        }
    }

    // 初始化并查集
    for (i = 0; i < mgraph.v; i++)
    {
        v[i] = i; //自己的根结点为自己
    }

    // 将图中各边按权值大小递增排列
    int min = road[0].weight;
    Road temp;
    for (i = 0; i < mgraph.e; i++)
    {
        for (j = i + 1; j < mgraph.e; j++)
        {
            if (road[j].weight < road[i].weight)
            {
                temp.a = road[i].a;
                temp.b = road[i].b;
                temp.weight = road[i].weight;

                road[i].a = road[j].a;
                road[i].b = road[j].b;
                road[i].weight = road[j].weight;

                road[j].a = temp.a;
                road[j].b = temp.b;
                road[j].weight = temp.weight;
            }
        }
    }

    int a, b;
    for (i = 0; i < mgraph.e; i++) // 依次检查按权值升序排列的边
    {
        a = getroot(road[i].a, v);
        b = getroot(road[i].b, v);
        if (a != b) // 边a----b的加入不会构成回路
        {
            // v[b] = a;
            v[a] = b; //对于边a----b，a可以是b的根，b也可以是a的根
            sum += road[i].weight;
            cout << road[i].a << "--" << road[i].weight << "--" << road[i].b << endl;
        }
    }
}

// 打印最短路径
void printpath(int path[], float dist[], int a, int v)
{
    int dest = a;
    int stack[v], top = -1;
    while (path[a] != -1)
    {
        stack[++top] = a;
        a = path[a]; // 最短路径上的前一个结点
    }
    stack[++top] = a; // 将源结点入栈
    while (top != -1)
    { // 出栈输出即为最短路径
        cout << "--->" << stack[top--];
    }
    cout << " length:" << dist[dest];
    cout << endl;
}

// 计算从源点v到其它结点的最短路径
/*
dijkstra是基于贪心策略，每次都找一个距源点最近的点，
然后将该距离定为这个点到源点的最短路径；
但如果存在负权边，那就有可能先通过并不是距源点最近的一个次优点，
再通过这个负权边，使得路径之和更小，这样就出现了错误。
*/
void dijkstra(MGraph mgraph, int v, float dist[], int path[])
{
    int set[mgraph.v] = {-1}; // 标记结点是否被并入最短路径
    float min;
    int i, j, u;

    // 初始化各个数组
    for (i = 0; i < mgraph.v; i++)
    {
        dist[i] = mgraph.edges[v][i]; // 源结点到其余各个结点的最短路径长度
        set[i] = 0;                   // 标记
        if (mgraph.edges[v][i] < DBL_MAX)
        {
            path[i] = v; // 源结点可直接到达其余结点，path[i] = v,表示从源结点v到结点vi的最短路径上的前一个顶点
        }
        else
        {
            path[i] = -1; // 源结点不能直接到达其余结点
        }
    }
    // 源结点并入最短路径
    set[v] = 1;
    path[v] = -1; // 源结点之前没有其他结点

    //********************************************
    cout << "dist: ";
    for (int k = 0; k < mgraph.v; k++)
    {
        cout << setiosflags(ios::left) << setw(5) << dist[k] << " ";
    }
    cout << endl;
    cout << "path: ";
    for (int k = 0; k < mgraph.v; k++)
    {
        cout << setiosflags(ios::left) << setw(5) << path[k] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
    //********************************************

    for (i = 0; i < mgraph.v - 1; i++)
    { //扫描图中剩余结点
        min = DBL_MAX;
        for (j = 0; j < mgraph.v; j++)
        { // 从剩余结点中选出一个结点，从源结点到剩余结点的路径中通往该结点的路径最短
            if (set[j] == 0 && dist[j] < min)
            {
                u = j;
                min = dist[j];
            }
        }

        set[u] = 1; // 将选出的结点并入最短路径
        // 以刚挑选出的结点为中间结点，对通往所有剩余结点的路径检测
        for (j = 0; j < mgraph.v; j++)
        {
            // 看源节点经由u到剩余结点的路径是否更短
            if (set[j] == 0 && dist[u] + mgraph.edges[u][j] < dist[j])
            {
                dist[j] = dist[u] + mgraph.edges[u][j];
                path[j] = u;
            }
        }
        cout << "dist: ";
        for (int k = 0; k < mgraph.v; k++)
        {
            cout << setiosflags(ios::left) << setw(5) << dist[k] << " ";
        }
        cout << endl;
        cout << "path: ";
        for (int k = 0; k < mgraph.v; k++)
        {
            cout << setiosflags(ios::left) << setw(5) << path[k] << " ";
        }
        cout << endl;
        cout << "-------------------------------------------------------" << endl;
    }
}
// bellman-ford,存在负权边的单源最短路径问题
typedef struct Edge
{
    int src, dest;
    float weight;
} Edge;
bool bellmanford(MGraph mgraph, int v, float dist[], int path[])
{
    for (int i = 0; i < mgraph.v; i++)
    {
        if (i == v)
        {
            dist[i] = 0;
        }
        else
        {
            dist[i] = DBL_MAX;
        }
        path[i] = -1;
    }
    Edge edge[mgraph.e];
    int c = 0;
    for (int src = 0; src < mgraph.v; src++)
    {
        for (int dest = 0; dest < mgraph.v; dest++)
        {
            if (mgraph.edges[src][dest] < DBL_MAX && src != dest)
            {
                edge[c].src = src;
                edge[c].dest = dest;
                edge[c].weight = mgraph.edges[src][dest];
                c++;
            }
        }
    }

    bool isRelax = true;
    int count = 0;
    for (int v = 0; v < mgraph.v - 1 && isRelax; v++)
    {

        isRelax = false;
        // 进行一轮松弛操作
        for (int e = 0; e < mgraph.e; e++)
        {
            if (dist[edge[e].src] < DBL_MAX && dist[edge[e].src] + edge[e].weight < dist[edge[e].dest])
            {
                dist[edge[e].dest] = dist[edge[e].src] + edge[e].weight;
                path[edge[e].dest] = edge[e].src;
                isRelax = true;
            }
        }
        count++;
    }
    bool negtive_circle = false;
    // 在进行一轮松弛操作，检查是否存在负权回路
    for (int e = 0; e < mgraph.e; e++)
    {
        if (dist[edge[e].src] + edge[e].weight < dist[edge[e].dest])
        {
            negtive_circle = true;
            break;
        }
    }
    return negtive_circle;
}

// floyd
void printpath(int u, int v, int **path)
{
    if (path[u][v] == -1)
    {
        cout << u << "--->";
    }
    else
    {
        int mid = path[u][v];
        printpath(u, mid, path);
        printpath(mid, v, path);
    }
}
void printarray(float **array, MGraph mgraph)
{
    for (int i = 0; i < mgraph.v; i++)
    {
        for (int j = 0; j < mgraph.v; j++)
        {
            cout << setiosflags(ios::left) << setw(5) << array[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd(MGraph mgraph, float **A, int **path)
{
    int i, j, k;
    // 二维数组动态初始化
    path = new int *[mgraph.v];
    A = new float *[mgraph.v];
    for (i = 0; i < mgraph.v; i++)
    {
        path[i] = new int[mgraph.v];
        A[i] = new float[mgraph.v];
    }
    // 初态
    for (i = 0; i < mgraph.v; i++)
    {
        for (j = 0; j < mgraph.v; j++)
        {
            A[i][j] = mgraph.edges[i][j];
            path[i][j] = -1;
        }
    }
    printarray(A, mgraph);
    cout << endl;
    //printarray(path, mgraph);
    cout << endl;
    // 以k为中间接待你，检测所有顶点对(i,j) 之间的最短路径
    for (k = 0; k < mgraph.v; k++)
    {
        for (i = 0; i < mgraph.v; i++)
        {
            for (j = 0; j < mgraph.v; j++)
            {
                if (A[i][j] > A[i][k] + A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
        printarray(A, mgraph);
        cout << endl;
        //printarray(path, mgraph);
        cout << endl;
    }
}

// 使用队列优化的bellman-ford算法
void bellman_fordpro(MGraph, int s, float dist[], int path)
{
}
int main()
{
    /*
0 1 4
1 0 4
1 2 -3
2 1 -3
0 2 5
2 0 5
*/
    int v, e;
    cout << "Input the vertexs and edges of graph: ";
    cin >> v >> e;
    MGraph mgraph = initMGraph(v, e);
    int src, dest, weight;
    cout << "input the edges(source destination weight):" << endl;
    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest >> weight;
        addedge(mgraph, src, dest, weight);
    }

    printgraph(mgraph);
    float dist[mgraph.v];
    int path[mgraph.v];
    if (!bellmanford(mgraph, 0, dist, path))
    {
        for (int i = 0; i < mgraph.v; i++)
        {
            cout << path[i] << " ";
        }
    }

    /*
0 1 5
0 3 7
1 2 4
1 3 2
2 0 3
2 1 3
2 3 2
3 2 1
*/
    /*
    int v, e;
    cout << "Input the vertexs and edges of graph: ";
    cin >> v >> e;
    MGraph mgraph = initMGraph(v, e);
    int src, dest, weight;
    cout << "input the edges(source destination weight):" << endl;
    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest >> weight;
        addedge(mgraph, src, dest, weight);
    }
    float **A;
    int **Path;
    floyd(mgraph, A, Path);
*/
    return 0;
}