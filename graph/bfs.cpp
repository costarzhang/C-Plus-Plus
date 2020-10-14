#include <iostream>
#include <list>
#include <string.h>
using namespace std;
class graph {
    int v; //图结点个数
    list<int> *adj;

 public:
    graph(int v);
    void addedge(int src, int dest);
    void printgraph();
    void bfs(int s);
    void BFS(int s);
};
graph::graph(int v) {
    this->v = v;
    // 边表，每个结点对应一个列表，存储与该节点相邻的结点，如果是有向图，则为该结点指向的结点
    this->adj = new list<int>[v];
}
void graph::addedge(int src, int dest) {
    src--;
    dest--;
    adj[src].push_back(dest);
    // adj[dest].push_back(src);
}
void graph::printgraph() {
    for (int i = 0; i < this->v; i++) {
        cout << "Adjacency list of vertex " << i + 1 << " is \n";
        list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); ++it) {
            cout << *it + 1 << " ";
        }
        cout << endl;
    }
}
// 广度优先遍历
void graph::bfs(int s) {
    bool *visited = new bool[this->v + 1];
    memset(visited, false, sizeof(bool) * (this->v + 1));
    visited[s] = true; // 访问该结点
    list<int> q; // 辅助队列
    q.push_back(s); //结点入队
    list<int>::iterator it;

    while (!q.empty()) {
        int u = q.front();
        cout << u + 1 << " ";
        q.pop_front();
        for (it = adj[u].begin(); it != adj[u].end(); ++it) {
            if (visited[*it] == false) {
                visited[*it] = true;
                q.push_back(*it);
            }
        }
    }
}
void graph::BFS(int s) {
    bool *visited = new bool[this->v + 1];
    memset(visited, false, sizeof(bool) * (this->v + 1));
    for (int i = 0; i < this->v; i++) {
        if (visited[i] == false) {
            //this->bfs(i, visited);
        }
    }
}
int main() {
    graph g(4);
    g.addedge(1, 2);
    g.addedge(2, 1);
    g.addedge(3, 4);
    g.addedge(4, 3);
    g.addedge(1, 3);
    g.addedge(3, 1);
    g.addedge(2, 4);
    g.addedge(4, 2);
    //g.printgraph();
    g.bfs(3);
    //g.BFS(1);
    return 0;
}
