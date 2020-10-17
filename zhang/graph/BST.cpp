#include <iostream>
#include <list>
using namespace std;



// 二叉排序树
/*
一颗二叉排序树：
    若左子树非空，则左子树上所有结点的关键字值小于根结点的关键字值
    若右子树非空，则右子树上所有结点的关键字值大于根结点的关键字值
    左右子树本身右是一颗二叉排序树
*/
typedef struct BTNode {
    int key;
    struct BTNode *left;
    struct BTNode *right;
}BTNode;

// 查找
BTNode *BSTsearch(BTNode *bt, int key) {
    if (bt == nullptr) {
        return nullptr;
    } else {
        if (bt->key == key) {
            return bt;
        } else if(key < bt->key) {
            return BSTsearch(bt->right, key);
        } else {
            return BSTsearch(bt->left, key);
        }
    }
}
// 层序遍历
void BFT(BTNode *bt) {
    list<BTNode *> queue;
    queue.push_back(bt);
    while (!queue.empty()) {
        bt = queue.front();
        cout << bt->key << "  ";
        queue.pop_front();
        if (bt->left != nullptr)
            queue.push_back(bt->left);
        if (bt->right != nullptr)
            queue.push_back(bt->right);
    }
}

// 插入结点
int BSTinsert (BTNode *&bt, int key) {
    if (bt == nullptr) {
        bt = new BTNode;
        bt->key = key;
        bt->right = bt->left = nullptr;
        return 1;
    } else {
        if(key == bt->key) { // 二叉排序树中各结点关键字值不相等
            return 0;
        } else if (key < bt->key) { // 插入结点的关键字值小于根节点值，则向根的左子树中插入
            return BSTinsert(bt->left, key);
        } else {
            return BSTinsert(bt->right, key);
        }
    }
}

// 删除结点
/*
           53                                           53
        /     \      删除45（仅有一棵子树）           /    \ 
      17       78    ------------------------->     17      78
    /   \     /  \                                /   \    /  \
   9     45  65   87                             9    23  65   87
        /
       23

             53                                                  53                                             53
           /    \                                              /    \                                         /    \
         17      78       删除78（有两棵子树）                17     81        从树中删除81                  17     81       
       /   \    /   \   ---------------------->             /   \   /   \    --------------------->        /   \   /   \
      9    45  65    94   以81替代78                       9    45 65    94                               9    45 65    94
          /         /                                          /        /                                     /        /
         23        81                                         23       81                                    23      88
                     \                                                   \
                      88                                                  88  
1.叶子结点直接删除
2.被删除结点仅有一颗子树，则以子树替代被删除结点
3.若被删除结点有两颗子树，则以该节点的直接后继（或者直接前驱）替代该结点
然后从树中删除这个直接后继（或者直接前驱），转换为1或者2的情况。这里的直接后继是指中序遍历序列的直接后继
*/
void BSTdelete(BTNode *&bt, int key) {
    BTNode *q, *s;
    if (bt == nullptr) {
        return;
    }else if (bt->key == key) {
        if (!bt->right && !bt->left) { // 找到结点直接删除
            q = bt;
            bt = nullptr;
            free(q);
        } else if (!bt->right) {  // 待删除结点仅有左子树
            q = bt;
            bt = bt->left; // 以其左子树代替
            free(q);
        }else if (!bt->left) { // 待删除结点仅有右子树
            q = bt;
            bt = bt->right; // 以其右子树代替
            free(q);
        } else { // 待删除结点的左右子树均不为空
            q = bt;
            s = bt->left;
            while (s->right != nullptr) { // 寻找结点前驱，q指向bt的直接前驱的父节点，bt的直接前驱有两种可能：1.bt的左孩子2.bt的左孩子的右孩子或者左孩子的右孩子的右孩子...
                q = s;
                s = s->right;
            }
            bt->key = s->key; // 以前驱替代
            if (q != bt) {//前驱是第二种情况
                q->right = s->left;
            } else {//前驱是第一种情况
                q->left = s->left;
            }
        }
    } else if(key < bt->key) {
        BSTdelete(bt->left, key);
    } else if (key > bt->key) {
        BSTdelete(bt->right,key);
    }
}

// 创建二叉排序树
void createBST(BTNode *&bt, int key[], int n) {
    int i;
    bt = nullptr;
    for (i = 0; i < n; i++) {
        BSTinsert(bt, key[i]);
    }
}

void BSTsort(BTNode *bt) {
    if (bt) {
        BSTsort(bt->left);
        cout << bt->key << " ";
        BSTsort(bt->right);
    }
}
int main() {
    int key[10] = {53, 17, 78, 9, 45, 46, 65, 60, 66, 94};
    BTNode *bt = nullptr;
    createBST(bt, key, 10);
    BFT(bt);
    BSTdelete(bt, 78);
    cout << endl;
    BFT(bt);
    cout << endl;
    return 0;
}