#include <iostream>
using namespace std;

// 线性表定义
typedef struct
{
    int *data;
    int length = 0;
    int maxsize = 0;
} seqlist;

// 初始化
int init(seqlist &l, int size, int incrcement)
{
    if (l.data = (int *)malloc((size + incrcement) * sizeof(int)))
    {
        l.length = 0;
        l.maxsize = size + incrcement;
        return 1;
    }
    else
    {
        return 0;
    }
}
// 顺序表扩容
int expansion(seqlist &l, int increment)
{
    l.data = (int *)realloc(l.data, (l.length + increment) * sizeof(int));
    if (l.data)
    {
        l.maxsize = l.length + increment;
        return 1;
    }
    else
    {
        return 1;
    }
}

// 插入
int insert(seqlist &l, int position, int e)
{
    if (l.length == l.maxsize)
    {
        expansion(l, 1); // 表空间满，扩容
    }
    if (position < 0 || position > l.length)
    {
        return 0;
    }
    for (int i = l.length - 1; i >= position; --i)
    {
        l.data[i + 1] = l.data[i];
    }
    l.data[position] = e;
    l.length++;
    return 1;
}
int deleteelem(seqlist &l, int position, int &e)
{
    if (position < 0 || position > l.length - 1)
    {
        return 0;
    }
    e = l.data[position];
    for (int i = position; i < l.length - 1; i++)
    {
        l.data[i] = l.data[i + 1];
        l.length--;
    }
    return 1;
}

int getposition(seqlist &l, int e)
{
    for (int i = 0; i < l.length; i++)
    {
        if (l.data[i] == e)
        {
            return i;
        }
    }
    return -1;
}

int getelem(seqlist &l, int position, int &e)
{
    if (position < 0 || position > l.length - 1)
    {
        return 0;
    }
    e = l.data[position];
    return 0;
}

void destroy(seqlist &l)
{
    free(l.data);
}
void clear(seqlist &l)
{
    l.data = 0;
}
void print(seqlist &l)
{
    for (int i = 0; i < l.length; i++)
    {
        cout << l.data[i] << " ";
    }
}

int main()
{

    seqlist l;
    init(l, 10, 0);
    l.data[0] = 8;
    l.data[1] = 3;
    l.data[2] = 3;
    l.data[3] = 3;
    l.data[4] = 3;
    l.data[5] = 2;
    l.data[6] = 3;
    l.data[7] = 5;
    l.data[8] = 3;
    l.data[9] = 8;
    l.length = 10;
    print(l);
    cout << endl;
    int i, j, k;
    k = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < k && l.data[i] != l.data[j]; j++)
            ;

        if (j == k)
        {
            if (k != i)
            {
                l.data[k] = l.data[i];
                k++;
            }
        }
    }
    l.length = k;
    print(l);
}