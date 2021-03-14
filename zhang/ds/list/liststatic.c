#include "liststatic.h"
#include <stdio.h>
// 初始化表空间
void InitializeCursorSpace()
{
    int i;
    for (i = 0; i < SpaceSize - 1; i++)
    {
        CursorSpace[i].next = i + 1;
    }
    CursorSpace[i].next = 0;
}
//分配空间
Position CursorAlloc()
{
    Position p;
    p = CursorSpace[0].next; //空闲空间均放在0之后
    CursorSpace[0].next = CursorSpace[p].next;
    CursorSpace[p].next = 0;
    return p;
}

static void CursorFree(Position p)
{
    CursorSpace[p].next = CursorSpace[0].next;
    CursorSpace[0].next = p;
}

int IsEmpty(List l)
{
    return CursorSpace[l].next == 0;
}

int IsLast(Position p, List l)
{
    return CursorSpace[p].next == 0;
}

Position Find(ElementType x, List l)
{
    Position p;
    p = CursorSpace[p].next;
    while (p && CursorSpace[p].e != x)
        p = CursorSpace[p].next;
    return p;
}

Position FindPrevious(ElementType x, List l)
{
    Position p, pre;
    pre = l;
    p = CursorSpace[pre].next;
    while (CursorSpace[p].e != x && p)
    {
        pre = p;
        p = CursorSpace[pre].next;
    }
    return pre;
}

void Delete(ElementType x, List l)
{
    Position p, tmpcell;
    do
    {
        p = FindPrevious(x, l);
        if (!IsLast(p, l))
        {
            tmpcell = CursorSpace[p].next;
            CursorSpace[p].next = CursorSpace[tmpcell].next;
            CursorFree(tmpcell);
        }
    } while (!IsLast(p, l));
}

void Insert(ElementType x, List l, Position p)
{
    Position tmpcell;
    tmpcell = CursorAlloc();
    if (tmpcell == 0)
        return;
    CursorSpace[tmpcell].e = x;
    if (IsLast(p, l))
    {
        CursorSpace[tmpcell].next = 0;
    }
    CursorSpace[tmpcell].next = CursorSpace[p].next;
    CursorSpace[p].next = tmpcell;
}

void printl(List l)
{
    Position p = CursorSpace[l].next;
    while (p)
    {
        printf("%c ", CursorSpace[p].e);
        p = CursorSpace[p].next;
    }
    printf("\n");
}