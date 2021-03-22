#include <iostream>
using namespace std;

// 树的孩子兄弟表示法
typedef struct TNode
{
    char data;
    struct TNode *firstchild, *nextsibling;
} * Tree;

/*创建树
tree 当前节点
pre 当前节点的父节点

*/
void create(Tree &tree, bool iffirstchild, bool ifnextsibling, TNode *pre)
{
    char data;
    if (iffirstchild)
    {
        cout << "输入" << pre->data << "的第一个孩子结点：";
        cin >> data;
    }
    else if (ifnextsibling)
    {
        cout << "输入" << pre->data << "的右兄弟结点：";
        cin >> data;
    }
    else
    {
        cout << "输入根结点：";
        cin >> data;
    }

    tree = (TNode *)malloc(sizeof(TNode));
    tree->data = data;
    tree->firstchild = nullptr;
    tree->nextsibling = nullptr;

    bool child, sibling;
    cout << tree->data << "是否有孩子和右兄弟结点：";
    cin >> child >> sibling;
    if (child)
    {
        create(tree->firstchild, child, false, tree);
    }
    if (sibling)
    {
        create(tree->nextsibling, false, sibling, tree);
    }
}
//先序遍历
void pre(Tree tree)
{
    if (tree != nullptr)
    {
        cout << tree->data << "  ";
        pre(tree->firstchild);
        pre(tree->nextsibling);
    }
}

int main()
{
    Tree tree = nullptr;
    create(tree, false, false, tree);
    pre(tree);
    pos(tree);
}