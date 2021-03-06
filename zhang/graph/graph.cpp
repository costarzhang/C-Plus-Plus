#include <iostream>
#include <float.h>
#include <iomanip>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

/**图
 * 任何图的所有顶点度数之和等于边数的2倍
 * 任何图都有偶数个奇度顶点
 * 
 * 含有n个顶点的无向完全图含有n(n-1) / 2条边，最大度为n-1
 * 含有n个顶点的有向完全图含有n(n-1)条边
 * 简单回路，回路中不存在重复的边
 * 
 * 可达矩阵，设有向图D=<V, E>, 顶点集<V1, V2, ..., Vn>
 * 定义矩阵P=(pij)n*n
 * 其中pij = 0(顶点Vi到Vj不可达)；pij = 1(顶点Vi到Vj可达)
 * B=A+A^2+A^3+...+A^n
 * 
 * 对于有n个顶点的图的邻接矩阵A,A^m中的元素Aij表示从顶点Vi到Vj的
 * 路径长度为m的路径条数
 * 
 * /

/*
极大连通子图：
1.连通图只有一个极大连通子图，就是它本身。（是唯一的）
2.非连通图有多个极大连通子图。（非连通图的极大连通子图叫做连通分量，每个分量都是一个连通图）
3.称为极大是因为如果此时加入任何一个不在图的点集中的点都会导致它不再连通。

极小连通子图：
1.一个连通图的生成树是该连通图顶点集确定的极小连通子图。（同一个连通图可以有不同的生成树，所以生成树不是唯一的）
（极小连通子图只存在于连通图中）
2.用边把极小连通子图中所有节点给连起来，若有n个节点，则有n-1条边。
3.之所以称为极小是因为此时如果删除一条边，就无法构成生成树，也就是说给极小连通子图的每个边都是不可少的。
4.如果在生成树上添加一条边，一定会构成一个环。
也就是说只要能连通图的所有顶点而又不产生回路的任何子图都是它的生成树。

极大强连通子图：
1.强连通图的极大强连通子图为其本身。（是唯一的）
2.非强连通图有多个极大强连通子图。（非强连通图的极大强连通子图叫做强连通分量）

####
带权联通图中所有边的权值不同 => 图的最小生成树唯一
带权联通图中任意一个环中包含的边的权值均不相等 => 图的最小生成树唯一
图的最小生成树唯一 <=> 对于非最小生成树的边，其权值与该边两端点在最小生成树上的路径最小边权值不相等
*/
/**
 * 十字链表存储有向图，整合邻接表与逆邻接表
 * 邻接多重表存储无向图
 * 
*/

// 邻接表存储图
//每条边存储该边指向的顶点，该边的权值，信息，以及下一条边，即弧尾相同的下一条边
typedef struct ArcNode
{                                      // 边表结点
    int adjvex;                        // 该边所指顶点编号，即弧头
    string info;                       // 该边的信息
    float weight;                      // 权值
    struct ArcNode *nextarc = nullptr; // 指向下一条边的指针

} AcrNode;
//顶点表存储图中所有结点
typedef struct VNode
{                                // 顶点表结点
    int data;                    // 顶点信息
    int incount;                 // 入度
    int outcount;                // 出度
    int timestamp_dfs = 0;       // 深度优先遍历时间戳
    ArcNode *firstarc = nullptr; // 指向第一条边的指针
    int iscutpoint = 0;
} VNode;
typedef struct AGraph
{                   // 邻接表
    int v;          // 顶点数
    int e;          // 边数
    VNode *adjlist; // 顶点表
    float **edges;  // 邻接矩阵
} AGraph;
//在逆邻接表的顶点表中，每个顶点存储指向该顶点的边
typedef struct VertAGraph
{                   // 逆邻接表
    int v;          // 顶点数
    int e;          // 边数
    VNode *adjlist; // 顶点表
    float **edges;  // 逆邻接矩阵
} VertAGraph;

// 十字链表弧结构
typedef struct CrossArcNode
{
    // 弧 src(弧尾)---->dest(弧头)
    int src;                        // 弧尾顶点
    int dest;                       // 弧头顶点
    struct CrossArcNode *src_next;  // 表示弧尾相同的下一条边，即src顶点的出边
    struct CrossArcNode *dest_next; // 表示弧头相同的下一条边，即dest顶点的入边
    float weight;                   //权值
    string info;                    // 弧的信息
    // 这样src顶点的所有出边被链成一个单链表，dest的所有入边被链成一个单链表
} CrossArcNode;
//十字链表顶点结构
typedef struct CrossVNode
{
    int data;
    CrossArcNode *firstin;  // 以该顶点为弧头的第一条弧，即指向该顶点的边所在的弧
    CrossArcNode *firstout; // 以该顶点为弧尾的第一条弧，即该顶点发出的边所在的弧
} CrossVNode;
typedef struct CrossGraph //十字链表
{
    int v;
    int e;
    CrossVNode *adjlist; //顶点表
} CrossGraph;

//邻接多重表边结构,每条边依附于两个顶点
typedef struct MulArcNode
{
    float weight; //边权值
    string info;
    int ivex;                 //顶点
    struct MulArcNode *ilink; // 依附于ivex顶点的另一条边
    int jvex;
    struct MulArcNode *jlink;
} MulArcNode;
//邻接多重表顶点结构
typedef struct MulVNode
{
    int data;
    MulArcNode *firstedge; // 第一条依附于该顶点的边
} MulVNode;
typedef struct MulGraph
{
    int v;
    int e;
    MulVNode *adjlist; // 顶点表
} MulGraph;

// 初始化邻接表
AGraph
initAGraph(int v, int e)
{
    AGraph agraph;
    agraph.v = v;                  // 结点数
    agraph.e = e;                  // 边数
    agraph.adjlist = new VNode[v]; // 顶点表
    // 初始化顶点表
    for (int i = 0; i < v; i++)
    {
        agraph.adjlist[i].data = i;
        agraph.adjlist[i].incount = 0;
        agraph.adjlist[i].outcount = 0;
        agraph.adjlist[i].firstarc = nullptr;
    }
    // 二维邻接矩阵初始化
    agraph.edges = new float *[v];
    for (int i = 0; i < v; i++)
    {
        agraph.edges[i] = new float[v];
    }
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i != j) //Vi到Vj不存在边
            {
                agraph.edges[i][j] = DBL_MAX;
            }
            else
            {
                agraph.edges[i][j] = 0; // 结点自己到自己的距离规定为0
            }
        }
    }
    return agraph;
}
// 初始化逆邻接表
VertAGraph initVAGraph(int v, int e)
{
    VertAGraph vagraph;
    vagraph.v = v;
    vagraph.e = e;
    vagraph.adjlist = new VNode[v];
    for (int i = 0; i < v; i++)
    {
        vagraph.adjlist[i].data = i;
        vagraph.adjlist[i].incount = 0;
        vagraph.adjlist[i].outcount = 0;
        vagraph.adjlist[i].firstarc = nullptr;
    }

    vagraph.edges = new float *[v];
    for (int i = 0; i < v; i++)
    {
        vagraph.edges[i] = new float[v];
    }
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i != j)
            {
                vagraph.edges[i][j] = DBL_MAX;
            }
            else
            {
                vagraph.edges[i][j] = 0; // 结点自己到自己的距离规定为0
            }
        }
    }
    return vagraph;
}

// 打印邻接矩阵
void print(AGraph agraph)
{
    cout << "*"
         << "  ";
    for (int k = 0; k < agraph.v; k++)
    {
        cout << setiosflags(ios::left) << setw(5) << k << "  ";
    }
    cout << endl;
    for (int i = 0; i < agraph.v; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < agraph.v; j++)
        {
            if (agraph.edges[i][j] < DBL_MAX)
            {
                cout << setiosflags(ios::left) << setw(5) << agraph.edges[i][j] << "  ";
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

// 打印逆邻接矩阵
void print1(VertAGraph vagraph)
{
    cout << "*"
         << "  ";
    for (int k = 0; k < vagraph.v; k++)
    {
        cout << setiosflags(ios::left) << setw(5) << k << "  ";
    }
    cout << endl;
    for (int i = 0; i < vagraph.v; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < vagraph.v; j++)
        {
            if (vagraph.edges[i][j] < DBL_MAX)
            {
                cout << setiosflags(ios::left) << setw(5) << vagraph.edges[i][j] << "  ";
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

// 添加边，vagraph 是图的逆邻接表存储，agraph是图的邻接表存储
void addedge(VertAGraph vagraph, AGraph agraph, int src, int dest, int weight, string ac)
{
    ArcNode *p = nullptr;

    // 生成一条新的边
    AcrNode *arcnode = new ArcNode;
    arcnode->adjvex = dest;     // src--->dest, dest表示弧头顶点
    arcnode->info = ac;         // 该边代表的活动
    arcnode->weight = weight;   // 边权值
    arcnode->nextarc = nullptr; //第一条出边

    // 处理该结点的第一个邻接点
    if (agraph.adjlist[src].firstarc == nullptr)
    {
        agraph.adjlist[src].firstarc = arcnode;
        agraph.adjlist[src].outcount += 1; // 源结点出度+1
        agraph.adjlist[dest].incount += 1; // 目标结点入度+1
        agraph.edges[src][dest] = weight;
    }
    else
    { // 遍历该节点的边表，找到位置插入新的边
        p = agraph.adjlist[src].firstarc;
        while (p->nextarc != nullptr)
        {
            p = p->nextarc;
        }
        // 将新的边接入
        p->nextarc = arcnode;
        agraph.adjlist[src].outcount += 1;
        agraph.adjlist[dest].incount += 1;
        agraph.edges[src][dest] = weight;
    }

    // 逆邻接表
    AcrNode *srcnode = new AcrNode;
    srcnode->adjvex = src; //dest<---src
    srcnode->nextarc = nullptr;
    arcnode->weight = weight;
    arcnode->info = ac;
    if (vagraph.adjlist[dest].firstarc == nullptr)
    {
        vagraph.adjlist[dest].firstarc = srcnode; // 逆邻接表中每个结点的边表存储的是指向该结点的边
        vagraph.adjlist[src].outcount += 1;
        vagraph.adjlist[dest].incount += 1;
        vagraph.edges[dest][src] = weight;
    }
    else
    { // 遍历该节点的边表，找到位置插入新的边
        p = vagraph.adjlist[dest].firstarc;
        while (p->nextarc != nullptr)
        {
            p = p->nextarc;
        }
        p->nextarc = srcnode;
        vagraph.adjlist[src].outcount += 1;
        vagraph.adjlist[dest].incount += 1;
        vagraph.edges[dest][src] = weight;
    }
}

// 打印邻接表
void printgraph(AGraph agraph)
{
    cout << "图的邻接表存储" << endl;
    for (int i = 0; i < agraph.v; i++)
    {
        ArcNode *p = agraph.adjlist[i].firstarc;
        if (p == nullptr)
        {
            cout << "[" << i << "]"
                 << " ---> null";
        }
        else
        {
            cout << "[" << i << "]"
                 << " ----> ";
        }
        while (p != nullptr)
        {
            if (p->nextarc == nullptr)
            {
                cout << p->adjvex << " ---> null";
            }
            else
            {
                cout << p->adjvex << " ----> ";
            }
            p = p->nextarc;
        }
        cout << endl;
    }
}

// 打印逆邻接表
void printvgraph(VertAGraph vagraph)
{
    cout << "图的邻接表存储" << endl;
    for (int i = 0; i < vagraph.v; i++)
    {
        ArcNode *p = vagraph.adjlist[i].firstarc;
        if (p == nullptr)
        {
            cout << "[" << i << "]"
                 << " <--- null";
        }
        else
        {
            cout << "[" << i << "]"
                 << " <---- ";
        }
        while (p != nullptr)
        {
            if (p->nextarc == nullptr)
            {
                cout << p->adjvex << " <--- null";
            }
            else
            {
                cout << p->adjvex << " <---- ";
            }
            p = p->nextarc;
        }
        cout << endl;
    }
}

// 打印顶点的出度与入度
void printinandout(AGraph agraph)
{
    for (int i = 0; i < agraph.v; i++)
    {
        cout << i << " in: " << agraph.adjlist[i].incount << " out: " << agraph.adjlist[i].outcount << endl;
    }
}

// 广度优先遍历 时间复杂度 O(V+E)[邻接表] O(V^2)[邻接矩阵]
void bfs(AGraph agraph, int v, int *visited, int &f)
{
    ArcNode *p;
    int j;
    int *que = new int[agraph.v];
    int front = 0, rear = 0; // 辅助队列

    // 访问顶点v
    cout << "--->" << v;
    // 访问标志置为1
    visited[v] = 1;
    // 将该结点入队
    rear = (rear + 1) % agraph.v;
    que[rear] = v;

    while (rear != front)
    { // 对列不空
        // 出队
        front = (front + 1) % agraph.v;
        j = que[front];
        p = agraph.adjlist[j].firstarc;
        // 将p所指结点的所有未被访问的邻接点入队
        while (p != nullptr)
        {
            if (visited[p->adjvex] == 0)
            {
                cout << "--->" << p->adjvex;
                visited[p->adjvex] = 1;
                rear = (rear + 1) % agraph.v; // 入队
                que[rear] = p->adjvex;
            }
            p = p->nextarc;
        }
    }
    f = j;
}

typedef struct note
{
    int v, s;
} note;
// 广度优先遍历求最短路径[无权值]
/*广度优先遍历每次先遍历同层结点，所以是最近的，基于贪心的思想
*/
void bfsmin(AGraph agraph, int v, int *visited, int dst, note que[])
{
    ArcNode *p;
    int j;
    int flag = 1;
    int front = 0, rear = 0; // 辅助队列

    // 访问标志置为1
    visited[v] = 1;
    // 将该结点入队
    rear = (rear + 1) % agraph.v;
    que[rear].v = v;
    que[rear].s = 0;
    while (rear != front)
    { // 对列不空
        // 出队
        front = (front + 1) % agraph.v;
        j = que[front].v;
        p = agraph.adjlist[j].firstarc;
        // 将p所指结点的所有未被访问的邻接点入队
        while (p != nullptr)
        {
            if (visited[p->adjvex] == 0)
            {
                visited[p->adjvex] = 1;
                rear = (rear + 1) % agraph.v; // 入队
                que[rear].v = p->adjvex;
                que[rear].s = que[front].s + 1;
            }
            if (que[rear].v == dst)
            { // 到达目标结点
                flag = 0;
                break;
            }
            p = p->nextarc;
        }
        if (!flag) //最短路径找到
            break;
    }
    cout << que[rear].v << "  " << que[rear].s;
}

// 深度优先遍历（递归）O(V+E)[邻接表] O(V^2)[邻接矩阵]
void dfs(AGraph agraph, int v, int *visited)
{
    ArcNode *p;

    cout << "--->" << v; //访问当前结点
    visited[v] = 1;

    p = agraph.adjlist[v].firstarc;
    while (p != nullptr)
    {
        if (visited[p->adjvex] == 0)
        {
            dfs(agraph, p->adjvex, visited);
        }
        p = p->nextarc;
    }
}

// 深度优先遍历（递归）求最短路径(仅找到最短路径长度，未记录路径)
void dfsmin(AGraph agraph, int v, int dst, int *visited, int dist, int &min)
{
    ArcNode *p;
    if (dist > min) //起始结点到达当前顶点的距离不是最短路径
        return;
    if (v == dst) //到达目标顶点
    {
        if (dist < min)
            min = dist; //更新最短路径长度
        return;
    }

    //访问当前结点
    visited[v] = 1;

    p = agraph.adjlist[v].firstarc;
    while (p != nullptr)
    {
        if (visited[p->adjvex] == 0)
        {
            dfsmin(agraph, p->adjvex, dst, visited, dist + p->weight, min);
            visited[p->adjvex] = 0;
        }
        p = p->nextarc;
    }
    return;
}

// [使用栈进行深度优先遍历]
void dfswithstack(AGraph agraph, int v, int *visited)
{
    ArcNode *p = nullptr;
    int top = -1;
    int *stack = new int[agraph.v]; // 辅助栈

    int i, k;

    cout << v << "--->"; // 访问v
    visited[v] = 1;
    stack[++top] = v; // 将起始顶点v入栈

    while (top != -1)
    {
        k = stack[top];
        p = agraph.adjlist[k].firstarc;

        // 找到栈顶结点的未被访问过的邻接点
        while (p != nullptr && visited[p->adjvex] == 1)
        {
            p = p->nextarc;
        }
        // 若栈顶结点的没有未被访问过的邻接点或者没有邻接点，将栈顶结点出栈
        if (p == nullptr)
        {
            --top;
        }
        else
        { // 如果栈顶结点有邻接点，则访问并入栈
            cout << p->adjvex << "--->";
            visited[p->adjvex] = 1;
            stack[++top] = p->adjvex;
        }
    }
}

// 拓扑排序(栈)
int *topsort(AGraph agraph)
{
    int i, j, n = 0;
    int *result = new int[agraph.v];
    int count = -1;
    int stack[agraph.v], top = -1; // 辅助栈
    AcrNode *p = nullptr;

    // 将入度为零的结点入栈
    for (i = 0; i < agraph.v; i++)
    {
        if (agraph.adjlist[i].incount == 0)
        {
            stack[++top] = i;
        }
    }

    while (top != -1)
    {
        i = stack[top--];
        ++n; // 统计当前结点
        cout << i << " ";
        result[++count] = i;
        p = agraph.adjlist[i].firstarc;

        // 将删除后的顶点所指向的所有顶点的入度减去一
        while (p != nullptr)
        {
            j = p->adjvex;
            --(agraph.adjlist[j].incount);
            if (agraph.adjlist[j].incount == 0)
            { // 将入度变为0的结点入栈
                stack[++top] = j;
            }
            p = p->nextarc;
        }
    }
    cout << endl;
    if (agraph.v = n)
    { // 排序成功，图为有向无环图
        return result;
    }
    else
    { // 排序失败，有向图中存在环
        return 0;
    }
}
// 拓扑排序(队列)
int topsort1(AGraph agraph)
{
    int i, j, n = 0;
    int *queue = new int[agraph.v + 1]; //辅助队列
    int front = 0;
    int rear = 0;
    AcrNode *p = nullptr;

    // 将入度为零的结点入队
    for (i = 0; i < agraph.v; i++)
    {
        if (agraph.adjlist[i].incount == 0)
        {
            rear = (rear + 1) % (agraph.v + 1);
            queue[rear] = i;
        }
    }

    while (rear != front)
    {
        front = (front + 1) % (agraph.v + 1);
        i = queue[front];
        ++n; // 统计当前结点
        cout << i << " ";
        p = agraph.adjlist[i].firstarc;

        // 将删除后的顶点所指向的所有顶点的入度减去一
        while (p != nullptr)
        {
            j = p->adjvex;
            --(agraph.adjlist[j].incount);
            if (agraph.adjlist[j].incount == 0)
            { // 将入度变为0的结点入队
                rear = (rear + 1) % (agraph.v + 1);
                queue[rear] = j;
            }
            p = p->nextarc;
        }
    }
    cout << endl;
    if (agraph.v = n)
    { // 排序成功，图为有向无环图
        return 1;
    }
    else
    { // 排序失败，有向图中存在环
        return 0;
    }
}

// 逆拓扑排序(逆邻接表存储)
int *verttopsort(VertAGraph vagraph)
{
    int i, j, n = 0;
    int top = -1;
    int *result = new int[vagraph.v];
    int count = -1;
    int *stack = new int[vagraph.v];
    AcrNode *p = nullptr;

    // 将出度为零的结点入栈
    for (i = 0; i < vagraph.v; i++)
    {
        if (vagraph.adjlist[i].outcount == 0)
        {
            stack[++top] = i;
        }
    }

    while (top != -1)
    {
        i = stack[top--];
        ++n;
        cout << i << " ";
        result[++count] = i;
        p = vagraph.adjlist[i].firstarc;
        // 将指向该删除顶点的所有顶点出度减去一
        while (p != nullptr)
        {
            j = p->adjvex;
            --(vagraph.adjlist[j].outcount);
            if (vagraph.adjlist[j].outcount == 0)
            { // 将出度为一的顶点入栈
                stack[++top] = j;
            }
            p = p->nextarc;
        }
    }
    cout << endl;
    if (vagraph.v = n)
    {
        return result;
    }
    else
    {
        return 0;
    }
}
// 拓扑排序（深度优先遍历)，仅适用有向无环图
void topsortbydfs(AGraph agraph, int v, int *visited)
{
    ArcNode *p;
    visited[v] = 1;
    p = agraph.adjlist[v].firstarc;
    while (p != nullptr)
    {
        if (visited[p->adjvex] == 0)
        {
            topsortbydfs(agraph, p->adjvex, visited); //图中无环，所以图中在最后一个顶点(汇点)处会退出算法
            cout << p->adjvex;
        }
        p = p->nextarc;
    }
}
/*求关键路径(从源点到汇点的路径中，具有最大路径长度的路径)*/
// 获取结点前继以及权值
void getPre(VertAGraph vagraph, int v, int &Prev, int &weight, int visited[])
{
    for (int i = 0; i < vagraph.v; i++)
    {
        if (v != i)
        { // 除去自身外的其它顶点
            if (visited[i] == 0 && vagraph.edges[v][i] < DBL_MAX)
            {
                visited[i] = 1;
                Prev = i;
                weight = vagraph.edges[v][i];
                return;
            }
        }
    }
}

// 计算事件(顶点)k最早发生时间[源点到k的最长路径长]
int *ve_k(int top[], VertAGraph vagraph)
{
    int *ve = new int[vagraph.v]; // 存储结果
    for (int i = 0; i < vagraph.v; i++)
    {
        ve[i] = 0;
    }

    for (int i = 1; i <= vagraph.v - 1; i++)
    {                                      // 根据拓扑序列，依次求剩余结点的ve
        int *visited = new int[vagraph.v]; //访问标记
        for (int k = 0; k < vagraph.v; k++)
        {
            visited[k] = 0;
        }
        for (int j = 0; j < vagraph.adjlist[top[i]].incount; j++) //遍历到达当前顶点的所有路径
        {
            int Prev, weight;
            getPre(vagraph, top[i], Prev, weight, visited); //找到当前顶点的未被访问过的前驱顶点
            if (ve[Prev] + weight > ve[top[i]])
            {
                ve[top[i]] = ve[Prev] + weight; //更新路径值
            }
        }
    }
    return ve;
}
// 获取结点后继以及权值
void getPost(AGraph agraph, int v, int &Post, int &weight, int visited[])
{
    for (int i = 0; i < agraph.v; i++)
    {
        if (v != i)
        { // 除去自身外的其它顶点
            if (visited[i] == 0 && agraph.edges[v][i] < DBL_MAX)
            {
                visited[i] = 1;
                Post = i;
                weight = agraph.edges[v][i];
                return;
            }
        }
    }
}
// 计算事件(顶点)k最迟到发生时间[min{vl(j)-wieght<k,j>}]，在不推迟整个工程完成的前提下，该事件最迟必须发生的事件
int *vl_k(int top[], AGraph agraph, int ve)
{
    int *vl = new int[agraph.v]; // 存储结果
    for (int i = 0; i < agraph.v; i++)
    {
        vl[i] = INT16_MAX;
    }
    vl[top[agraph.v - 1]] = ve;
    for (int i = agraph.v - 2; i >= 0; i--)
    { // 根据逆拓扑序列，依次求剩余结点的ve
        int *visited = new int[agraph.v];
        for (int k = 0; k < agraph.v; k++)
        {
            visited[k] = 0;
        }
        for (int j = 0; j < agraph.adjlist[top[i]].outcount; j++) //遍历当前顶点的后继结点
        {
            int Post, weight;
            getPost(agraph, top[i], Post, weight, visited);
            if (vl[Post] - weight < vl[top[i]]) //跟新最小值
            {
                vl[top[i]] = vl[Post] - weight;
            }
        }
    }
    return vl;
}

//恢复图状态
void restore(AGraph agraph)
{
    for (int i = 0; i < agraph.v; i++)
    {
        agraph.adjlist[i].incount = agraph.adjlist[i].outcount = 0;
    }
    for (int i = 0; i < agraph.v; i++)
    {
        for (int j = 0; j < agraph.v; j++)
        {
            if (i != j)
            {
                if (agraph.edges[i][j] < DBL_MAX)
                {
                    agraph.adjlist[i].outcount += 1;
                    agraph.adjlist[j].incount += 1;
                }
            }
        }
    }
}
// 计算活动(边)最早开始时间，活动的最早发生时间即为发出该活动的事件的最早发生时间
void e_k(AGraph agraph, int *ve, map<string, int> &e)
{
    for (int i = 0; i < agraph.v; i++)
    {
        ArcNode *p = agraph.adjlist[i].firstarc;
        while (p != nullptr)
        {
            string ac = p->info;
            e[ac] = ve[i];
            p = p->nextarc;
        }
    }
}
//计算活动最迟发生时间[Vl(j)-weight<k,j>]
void l_k(AGraph agraph, int *vl, map<string, int> &l)
{
    for (int i = 0; i < agraph.v; i++)
    {
        ArcNode *p = agraph.adjlist[i].firstarc;
        while (p != nullptr)
        {
            string ac = p->info;
            l[ac] = vl[p->adjvex] - p->weight;
            p = p->nextarc;
        }
    }
}
//求解关键路径
void key_route(map<string, int> &e, map<string, int> l, AGraph &agraph)
{
    // 关键路径上的活动即关键活动
    // 关键活动的最早开始时间和最迟开始时间相等
    int length = 0;
    map<string, int>::iterator loop;
    for (loop = e.begin(); loop != e.end();)
    {
        if (loop->second == l[loop->first])
        { // 检查活动最早开始时间和最迟开始时间是否相等
            loop++;
        }
        else
        {
            loop = e.erase(loop++); // 从map中删除非关键活动
        }
    }
    restore(agraph);
    int source, i;
    for (i = 0; i < agraph.v; i++) //寻找汇点
    {
        if (agraph.adjlist[i].incount == 0)
        {
            source = i;
            break;
        }
    }
    cout << "关键路径:" << endl;
    cout << source "----> ";
    ArcNode *p = agraph.adjlist[i].firstarc;
    while (p != nullptr)
    {
        if (e.count(p->info))
        {
            cout << p->adjvex "----> ";
        }
        p = agraph.adjlist[p->adjvex].firstarc;
    }
}
/**
 * 求图的割点
 * agraph 图
 * curr 当前访问的顶点
 * pre curr的父亲顶点
 * timestamp 时间戳计数
 * low[] 记录顶点在不经过父顶点能够回到较早访问的顶点
 * root深度优先遍历起始顶点（根顶点）
 * 原理：若过某个顶点存在一个子顶点，能够不经过其回到在此顶点之前就访问过的顶点，
 则该顶点便不是割点，相反，如果某个顶点存在一个子顶点不能够不经过其回到在此顶点之前
 就访问过的顶点，那么此顶点便是一个割点
 */
void dfscut(AGraph agraph, int curr, int pre, int &timestamp, int low[], int root)
{
    ArcNode *p; //工作指针
    int child;  // 记录深度优先生成树中curr顶点的子顶点

    timestamp++; //每遍历到一个顶点，时间戳计数+1，记录每个顶点被访问的次序

    agraph.adjlist[curr].timestamp_dfs = timestamp;
    low[curr] = timestamp; //当前顶点能够回到的最早被访问的顶点的时间戳

    p = agraph.adjlist[curr].firstarc;
    while (p != nullptr)
    {
        if (agraph.adjlist[p->adjvex].timestamp_dfs == 0) //当前顶点未被访问
        {
            child++; //孩子顶点数+1
            dfscut(agraph, p->adjvex, curr, timestamp, low, root);
            // 更新当前顶点可以不经过其父顶点回到更早访问顶点的时间戳
            low[curr] = low[curr] < low[p->adjvex] ? low[curr] : low[p->adjvex];

            // 如果当前顶点curr不是根顶点
            if (curr != root && low[p->adjvex] >= agraph.adjlist[curr].timestamp_dfs)
            { //curr的子顶点中存在一个顶点p->adjvex不经过curr到达更早访问过的顶点
                agraph.adjlist[curr].iscutpoint = 1;
            }
            //如果当前顶点为根顶点，当其有两个孩子顶点时，其为割点
            if (curr == root && child == 2)
            {
                agraph.adjlist[curr].iscutpoint = 1;
            }
        }
        // p-->adjvex被访问过并且其不是curr的父顶点，其实就是要求curr不经过其父顶点回到更早早访问顶点
        else if (p->adjvex != pre)
        {
            low[curr] = low[curr] < agraph.adjlist[p->adjvex].timestamp_dfs ? low[curr] : agraph.adjlist[p->adjvex].timestamp_dfs;
        }

        p = p->nextarc;
    }
}

// 求图的割边
/**将图进行深度优先遍历，记录顶点遍历顺序，当一个顶点的邻接点中存在一个顶点不能经过除该
 * 结点以外的其他顶点回到在该顶点之前访问过的点以及该顶点自身，则该顶点和此邻接点组成的
 * 边即为图的一条割边
 */
void cutedge(AGraph agraph, int curr, int pre, int &timestamp, int low[], int root)
{
    ArcNode *p; //工作指针

    timestamp++; //每遍历到一个顶点，时间戳计数+1，记录每个顶点被访问的次序

    agraph.adjlist[curr].timestamp_dfs = timestamp;
    low[curr] = timestamp; //当前顶点能够回到的最早被访问的顶点的时间戳

    p = agraph.adjlist[curr].firstarc;
    while (p != nullptr)
    {
        if (agraph.adjlist[p->adjvex].timestamp_dfs == 0) //当前顶点未被访问
        {
            cutedge(agraph, p->adjvex, curr, timestamp, low, root);
            // 更新当前顶点可以不仅过其父顶点回到更早访问顶点的时间戳
            low[curr] = low[curr] < low[p->adjvex] ? low[curr] : low[p->adjvex];

            // 如果当前顶点curr不是根顶点
            if (curr != root && low[p->adjvex] > agraph.adjlist[curr].timestamp_dfs)
            { //curr的子顶点中存在一个顶点p->adjvex不经过curr到达更早访问过的顶点
                cout << curr << "---" << p->adjvex << endl;
            }
        }
        // p-<adjvex被访问过并且其不是curr的父节点，其实就是要求curr不经过其父顶点回到跟早访问顶点
        else if (p->adjvex != pre)
        {
            low[curr] = low[curr] < agraph.adjlist[p->adjvex].timestamp_dfs ? low[curr] : agraph.adjlist[p->adjvex].timestamp_dfs;
        }

        p = p->nextarc;
    }
}
int main()
{
    AGraph agraph = initAGraph(4, 8);
    VertAGraph vagraph = initVAGraph(4, 8);

    addedge(vagraph, agraph, 0, 1, 1, "a0");
    addedge(vagraph, agraph, 1, 0, 1, "a1");
    addedge(vagraph, agraph, 0, 2, 1, "a2");
    addedge(vagraph, agraph, 2, 0, 1, "a3");
    addedge(vagraph, agraph, 1, 2, 1, "a4");
    addedge(vagraph, agraph, 2, 1, 1, "a5");
    addedge(vagraph, agraph, 1, 3, 1, "a5");
    addedge(vagraph, agraph, 3, 1, 1, "a5");

    int timestamp = 0;
    int low[agraph.v];
    cutedge(agraph, 0, 0, timestamp, low, 0);
    /*
    int visited[5];
    for (int i = 0; i < 5; i++)
        visited[i] = 0;
    int dist = 0;
    int min = INT32_MAX;
    dfsmin(agraph, 0, 3, visited, dist, min);
    cout << min;
    */
    /*
    int visited[5];
    for (int i = 0; i < 5; i++)
        visited[i] = 0;
    note que[agraph.v];
    for (int i = 0; i < 5; i++)
    {
        que[i].s = que[i].v = 0;
    }
    bfsmin(agraph, 0, visited, 3, que);
    */
    /*
    int *top = topsort(agraph);
    printinandout(agraph);
    restore(agraph);
    printinandout(agraph);
    int *ve = ve_k(top, vagraph);
    for (int i = 0; i < agraph.v; i++) {
        cout << ve[i] << " ";
    }
    cout << endl;

    int *vl = vl_k(top, agraph, ve[top[agraph.v-1]]);
     for (int i = 0; i < agraph.v; i++) {
        cout << vl[i] << " ";
    }
    cout << endl;

    map<string,int> e;
    e_k(agraph, ve, e);
    map<string,int>::iterator iter;
    for(iter = e.begin(); iter != e.end(); iter++) {
        cout << "[" << iter->first << "," << iter->second << "]";
    }
    cout << endl;

    map<string,int> l;
    l_k(agraph, vl, l);
    map<string,int>::iterator iter1;
    for(iter1 = l.begin(); iter1 != l.end(); iter1++) {
        cout << "[" << iter1->first << "," << iter1->second << "]";
    }
    cout << endl;

    key_route(e, l, agraph);
    */

    return 0;
}

/*判断图有无环
1、拓扑排序 
    1.1、无向图
        使用拓扑排序可以判断一个无向图中是否存在环，具体步骤如下：
        求出图中所有结点的度。 将所有度 <= 1 的结点入队。（独立结点的度为 0） 
        当队列不空时，弹出队首元素，把与队首元素相邻节点的度减一。如果相邻节点的度变为一，则将相邻结点入队。
        循环结束时判断已经访问的结点数是否等于 n。等于 n 说明全部结点都被访问过，无环；反之，则有环。 
    1.2、有向图
        使用拓扑排序判断无向图和有向图中是否存在环的区别在于：
        在判断无向图中是否存在环时，求的是结点的度；
        在判断有向图中是否存在环时，求的是结点的入度。
2、DFS
使用 DFS 可以判断一个无向图和有向中是否存在环。
深度优先遍历图，如果在遍历的过程中，发现某个结点有一条边指向已访问过的结点，
并且这个已访问过的结点不是上一步访问的结点，则表示存在环。
3、Union-Find Set
我们可以使用并查集来判断一个图中是否存在环：

对于无向图来说，在遍历边（u-v）时，如果结点 u 和结点 v 的“父亲”相同，那么结点 u 和结点 v 在同一个环中。

对于有向图来说，在遍历边（u->v）时，如果结点 u 的“父亲”是结点 v，那么结点 u 和结点 v 在同一个环中。
*/
