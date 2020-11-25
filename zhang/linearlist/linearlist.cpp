#include <iostream>
using namespace std;

// 线性表定义
typedef struct
{
    int *data;
    int length = 0;
} seqlist;

// 初始化
int init(seqlist &l, int size, int incrcement)
{
    if (l.data = (int *)malloc((size + incrcement) * sizeof(int)))
    {
        l.length = 0;
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
    if (l.data = (int *)realloc(&l, (sizeof(l) + increment) * sizeof(int)))
    {
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
    if (l.length == sizeof(l.data))
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
    free(&l);
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

    /*
    seqlist l;
    init(l, 1, 0);
    insert(l, 0, 1);
    insert(l, 1, 2);
    print(l);
    */
}