#ifndef _LIST_H_

typedef ElementType int;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

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

#endif