#include <iostream>
#include <string.h>
using namespace std;

// 哈夫曼树存储结构，顺序存储
typedef struct HTNode
{
    int weight; // 结点权值
    char key;   // 叶子结点代表的字符
    int parent, left, right;
} HTNode;

// 选择权值最小的两颗树
void Select(HTNode *ht, int n, int &s1, int &s2)
{
    s1 = s2 = 0;
    int i;
    // 找到两个没有双亲结点的结点
    for (i = 1; i <= n; ++i)
    {
        if (0 == ht[i].parent)
        { // i没有双亲结点
            if (0 == s1)
            {
                s1 = i;
            }
            else
            {
                s2 = i;
                break;
            }
        }
    }
    // s1存储最小权值结点，s2存储次小权值结点
    if (ht[s1].weight > ht[s2].weight)
    {
        int t = s1;
        s1 = s2;
        s2 = t;
    }

    for (i += 1; i <= n; ++i)
    {
        if (0 == ht[i].parent)
        {
            if (ht[i].weight < ht[s1].weight)
            {
                s2 = s1;
                s1 = i;
            }
            else if (ht[i].weight < ht[s2].weight)
            {
                s2 = i;
            }
        }
    }
}
void createHuffmanTree(HTNode *&ht)
{
    int n, m; // 叶子结点数量以及哈夫曼树结点数量
    cout << "输入叶子结点数量: ";
    cin >> n;
    m = 2 * n - 1;
    ht = new HTNode[m + 1]; // 0号单元不存储结点信息

    // 初始化
    for (int i = 1; i <= m; ++i)
    {
        ht[i].parent = ht[i].left = ht[i].right = 0;
        ht[i].key = '*';
    }
    // 输入叶子结点的权值
    cout << "输入权值:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> ht[i].weight;
    }
    ht[0].weight = m; //结点数量
    // 建树
    for (int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(ht, i - 1, s1, s2);
        cout << "S1: " << s1 << "   S2: " << s2 << endl;
        ht[s1].parent = ht[s2].parent = i;
        ht[i].left = s1;
        ht[i].right = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        ht[i].parent = 0;
    }
}

void encode(HTNode *ht)
{
    int n = (ht[0].weight + 1) / 2;
    char **hc = (char **)malloc((n + 1) * sizeof(char *));
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '#';
    int start;
    for (int i = 1; i <= n; i++)
    {
        start = n - 1;
        int p = ht[i].parent;
        for (int j = i; p != 0; j = p, p = ht[p].parent)
        {
            if (ht[p].left == j)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
        }
        // 一个字符编码完，保存
        hc[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(hc[i], &cd[start]);
    }
    for (int i = 1; i <= n; i++)
    {
        int j = 0;
        while (hc[i][j] != '#')
        {
            cout << hc[i][j] << " ";
            j++;
        }
        cout << endl;
    }
    free(cd);
}

int getWSl(HTNode *ht)
{
    int result = 0;
    int temp = 0;
    for (int i = 1; i <= (ht[0].weight + 1) / 2; i++)
    {
        int j = i;
        temp = 0;
        while (ht[j].parent != 0)
        {
            j = ht[j].parent;
            temp++;
        }
        result += (temp * ht[i].weight);
    }
    return result;
}
int main()
{
    HTNode *ht;
    createHuffmanTree(ht);
    encode(ht);
    cout << getWSl(ht) << endl;
    return 0;
}