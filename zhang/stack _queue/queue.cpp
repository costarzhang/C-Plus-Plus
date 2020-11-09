#include <iostream>
using namespace std;
#define maxsize 4

// 队列
struct queue
{
    int *qu;
    int front, rear;
};

void initQueue(queue &queue)
{
    queue.front = queue.rear = 0; // 队列空
    queue.qu = (int *)malloc(sizeof(int) * maxsize);
}

int isEmpty(queue &queue)
{
    if (queue.front == queue.rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull(queue queue)
{
    if ((queue.rear + 1) % maxsize == queue.front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int enQueue(queue &queue, int x)
{
    if ((queue.rear + 1) % maxsize == queue.front)
    {
        return 0;
    }
    queue.rear = (queue.rear + 1) % maxsize;
    queue.qu[queue.rear] = x;
    return 1;
}

int deQueue(queue &queue, int &x)
{
    if (queue.front == queue.rear)
    {
        return 0;
    }
    queue.front = (queue.front + 1) % maxsize;
    x = queue.qu[queue.front];
    return 1;
}

int main()
{
    queue q;
    initQueue(q);
    int x;
    for (int i = 0; i < 4; i++)
    {
        if (enQueue(q, i))
        {
            cout << "success!" << endl;
        }
        else
        {
            cout << "fail!" << endl;
        }
    }
}