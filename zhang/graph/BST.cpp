#include <iostream>
#include <list>
using namespace std;



// 二叉排序树
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
        if(key == bt->key) {
            return 0;
        } else if (key < bt->key) {
            return BSTinsert(bt->left, key);
        } else {
            return BSTinsert(bt->right, key);
        }
    }
}

// 删除结点
void BSTdelete(BTNode *&bt, int key) {
    BTNode *q, *s;
    if (bt == nullptr) {
        return;
    }else if (bt->key == key) {
        if (!bt->right && !bt->left) {
            q = bt;
            bt = nullptr;
            free(q);
        } else if (!bt->right) {  // 待删除结点仅有左子树
            q = bt;
            bt = bt->left;
            free(q);
        }else if (!bt->left) { // 待删除结点仅有右子树
            q = bt;
            bt = bt->right;
            free(q);
        } else { // 待删除结点的左右子树均不为空
            q = bt;
            s = bt->left;
            while (s->right != nullptr) {
                q = s;
                s = s->left;
            }
            bt->key = s->key;
            if (q != bt) {
                q->right = s->left;
            } else {
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
    int key[7] = {5, 4, 8, 3, 7, 9, 10};
    BTNode *bt = nullptr;
    createBST(bt, key, 7);
    BFT(bt);
    BSTdelete(bt, 5);
    cout << endl;
    BFT(bt);
    cout << endl;
    BSTsort(bt);
    return 0;
}