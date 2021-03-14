#ifndef _LISTSTATIC_H

typedef char ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
#define SpaceSize 10
void InitializeCursorSpace();

List MakeEmpty(List l);
int IsEmpty(List l);
int IsLast(Position p, List l);
Position Find(ElementType x, List l);
void Delete(ElementType x, List l);
Position FindPrevions(ElementType x, List l);
void Insert(ElementType x, List l, Position p);
void DeleteList(List l);
Position Header(List l);
Position First(List l);
Position Advance(Position p);
ElementType Retrieve(Position p);

Position CursorAlloc();
static void CursorFree(Position p);
void printl(List l);
#endif

typedef struct Node
{
    ElementType e;
    Position next;
} Node;

Node CursorSpace[10];