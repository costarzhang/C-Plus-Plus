#include <stdio.h>

typedef int elem_type;
/*左式堆*/
typedef struct tree_node
{
    elem_type e;
    struct tree_node *left;
    struct tree_node *right;
    int npl; //零路径长度
} * priority_queue;
priority_queue merge1(priority_queue h1, priority_queue h2)
{
    if (!h1->left)
        h1->left = h2;
    else
    {
        h1->right = merge(h1->right, h2);
        if (h1->left->npl < h1->right->npl)
        {
            priority_queue p;
            p = h1->right;
            h1->right = h1->left;
            h2->left = p;
        }
        h1->npl = h1->right->npl + 1;
    }
    return h1;
}
priority_queue merge(priority_queue h1, priority_queue h2)
{
    if (!h1)
        return h1;
    if (!h2)
        return h2;
    if (h1->e < h2->e)
        return merge1(h1, h2);
    else
        return merge1(h2, h1);
}