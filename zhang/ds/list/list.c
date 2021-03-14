#include <stdio.h>
#include <stdlib.h>
#include "list.h"
struct Node //表节点定义
{
    int e;
    Position Next;
} Node;

int IsEmpty(List l) //判断表是否为空
{
    return l->Next == NULL;
}

int IsLast(Position p, List l) //判断当前元素是否是表尾元素
{
    return p->Next == NULL;
}

Position Find(int x, List l)
{
    Position p = l->Next;
    while (p != NULL && p->e != x)
    {
        p = p->Next;
    }
    return p;
}

Position FindPrevions(int x, List l)
{
    Position p = l;
    while (p->Next != NULL && p->Next->e != x)
    {
        p = p->Next;
    }
    return p;
}

void Delete(int x, List l)
{
    Position p, tmp;
    p = FindPrevions(x, l);
    if (!IsLast(p, l))
    {
        tmp = p->Next;
        p->Next = tmp->Next;
        free(tem);
    }
}

void Insert(int x, List l, Position p)
{
    Position tmp;
    tmp = (Position *)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        printf("内存不足！\n");
    }
    tmp->e = x;
    tmp->Next = p->Next;
    p->Next = tmp;
}

void DeleteList(List l)
{
    Position p, tmp;
    p = l->Next;
    l->Next = NULL;
    while (p != NULL)
    {
        tmp = p->Next;
        free(p);
        p = tmp;
    }
}