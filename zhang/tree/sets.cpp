#include <iostream>
using namespace std;

// 并查集

int sets[10];

void init(int s[])
{
    for (int i = 0; i < s.length(); i++)
        s[i] = -1; // 每个结点各自组成一个集合
}

void find(int s[], int x)
{
    while (s[x] >= 0)
    {
        x = s[x];
    }
    return x;
}

void unin(int s[], int root1, int root2)
{
    s[root2] = root1; // 将root2作为root1的一个孩子
}