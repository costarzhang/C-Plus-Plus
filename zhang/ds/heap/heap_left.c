#include <stdio.h>

typedef int elem_type;
/*左式堆*/
typedef struct tree_node
{
    elem_type e;
    struct tree_node *left;
    struct tree_node *right;
    int NPL; //零路径长度
} * priority_queue;



