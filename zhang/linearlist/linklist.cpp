#include <iostream>
using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *Linklist;

// 带头结点的单链表
int insert(Linklist &l, int position, int e)
{
    if (position < 1)
        return 0;
    LNode *p;
    int count = 0;
    p = l;
    while (p != nullptr && count < position - 1)
    {
        count++;
        p = p->next;
    }
    if (p == nullptr)
        return 0;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}
int main()
{
    // 建立单链表，带头节点
    Linklist = (LNode *)malloc(sizeof(LNode));
}