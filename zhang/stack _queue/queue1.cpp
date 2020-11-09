#include <iostream>
using namespace std;
#define maxsize 4
// 循环队列
typedef struct
{
    int *qu;
    int front, rear; // 队头，队尾
    int tag;         // 标记队列是否为空
} queue;

// 初始化
void initQueue(queue &qu)
{
    qu.front = qu.rear = 0;
    qu.tag = 0;
    qu.qu = (int *)malloc(maxsize * sizeof(int));
}

int isEmpty(queue qu)
{
    if (qu.front == qu.rear && qu.tag == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull(queue qu)
{
    if (qu.tag == 1 && qu.front == qu.rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int enQueue(queue &qu, int x)
{
    if (isFull(qu))
    {
        return 0;
    }
    else
    {
        qu.rear = (qu.rear + 1) % maxsize;
        qu.qu[qu.rear] = x;
        qu.tag = 1;
        return 1;
    }
}

int deQueue(queue &qu, int &x)
{
    if (isEmpty(qu))
    {
        return 0;
    }
    else
    {
        qu.front = (qu.front + 1) % maxsize;
        x = qu.qu[qu.front];
        qu.tag = 0;
        return 1;
    }
}

int main()
{
    queue qu;
    initQueue(qu);
    int x;
    for (int i = 0; i < 5; i++)
    {
        if (enQueue(qu, i))
        {
            cout << "success!" << endl;
        }
        else
        {
            cout << "fail!" << endl;
        }
    }
}
