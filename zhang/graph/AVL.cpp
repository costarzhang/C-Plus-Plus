#include <iostream>
#include <list>
using namespace std;

// 表示树的平衡因子是否改变(即树高是否变化)
#define LH +1 // 左高
#define EH 0 // 等高
#define RH -1 // 右高

typedef struct BSTNode {
    int key;
    int bf; // 平衡因子
    struct BSTNode *left, *right;
}BSTNode, *BSTree;

// 单右旋操作
void R_Rotate(BSTNode *&p) {
    // 对以p为根节点的二叉排序树作右旋处理
    BSTNode *l = p->left; // l指向p左子树的根
    p->left = l->right; // l的右子树成为p的左子树
    l->right = p; // l成为新的根节点
    p = l;
}

// 单左旋操作
void L_Rotate(BSTNode *&p) {
    // 对以p为根节点的二叉排序树作左旋处理
    BSTNode *r = p->right; // r指向p的右子树的根节点
    p->right = r->left; // r的左子树成为p的右子树
    r->left = p; // r成为新的根节点
    p = r;
}

// 左平衡处理
void leftBalance(BSTNode *&bt) {
    BSTNode *l = bt->left;
    BSTNode *r;
    switch (l->bf) {
        case LH:// LL型 l的原左子树比右子树高1，若在l的右子树中插入结点
                // 则无需处理，若在l的左子树中插入结点 
            bt->bf = l->bf = EH; // 做单右旋处理
            R_Rotate(bt); break;
        case RH: // LR型 //l的左子树比右子树低
            r = l->right;
            switch (r->bf) { // 调整平衡因子
                case LH: // 原r的左子树比右子树高1
                    bt->bf = RH; l->bf = EH; break;
                case EH:
                    bt->bf = l->bf = EH; break;
                case RH:
                    bt->bf = EH; l->bf = LH; break;
            }
            r->bf = EH;
            L_Rotate(bt->left); //  对bt的左子树作左旋处理
            R_Rotate(bt); // 对bt作右旋处理
            break;
    }
}
// 右平衡处理
void rightbalance(BSTNode *&bt) {
    BSTNode *r = bt->right;
    BSTNode *l;
    switch (r->bf) {
        case RH: // RR
            bt->bf = r->bf = EH;
            L_Rotate(bt);
            break;
        case LH: // RL
            l = r->left;
            switch (l->bf) {
                case LH:
                    bt->bf = RH; r->bf = EH; break;
                case EH:
                    bt->bf = r->bf = EH; break;
                case RH:
                    bt->bf = EH; l->bf = RH; break;
            }
            l->bf = EH;
            R_Rotate(bt->right);
            L_Rotate(bt);
    }
}

// 插入结点
int insertAVL(BSTNode *&bt, int key, bool &taller) {
    // 树为空
    if (!bt) {
        bt = new BSTNode;
        bt->key = key;
        bt->left = bt->right = nullptr;
        bt->bf = EH; // 此时树中只有一个结点，故其平衡因子为0
        taller = true; // 树的高度变化了
    } else { //树非空树
        if (bt->key == key) { // 结点重复，插入失败
            taller = false;
            return 0;
        }
        if (key < bt->key) { // 去左子树中操作
            if (!insertAVL(bt->left, key, taller)) {
                return 0; // 没有插入
            }
            if (taller) { // 结点已经插入到左子树中，且左子树长高
                switch (bt->bf) {
                    case LH:
                        // 原左子树比右子树高1，在左子树插入一个结点后，
                        // 左子树比右子树高2, 需要进行做平衡处理
                        leftBalance(bt); taller = false; break; // 调平衡
                    case EH:
                        // 原来左右子树等高，现在左子树中插入一个结点，
                        // 左子树将比右子树高1
                        bt->bf = LH; taller = true; break;
                    case RH:
                        // 原来右子树比左子树高1，现在左子树
                        // 中插入一个结点，且左子树长高，左右子树等高
                        bt->bf = EH; taller = false; break;
                }
            }
        } else { // 到右子树中操作
            if (!insertAVL(bt->right, key, taller)) {
                return 0;
            }
            if (taller) {
                switch (bt->bf) {
                    case LH:
                        bt->bf = EH; taller = false; break;
                    case EH:
                        bt->bf = RH; taller = true; break;
                    case RH:
                        rightbalance(bt); taller = false; break; // 调平衡
                }
            }
        }
    }
    return taller;
}

// 层序遍历
void BFT(BSTNode *bt) {
    list<BSTNode *> queue;
    queue.push_back(bt);
    while (!queue.empty()) {
        bt = queue.front();
        cout << bt->key << "(" << bt->bf << ")  ";
        queue.pop_front();
        if (bt->left != nullptr)
            queue.push_back(bt->left);
        if (bt->right != nullptr)
            queue.push_back(bt->right);
    }
    cout << endl;
}

int main() {
    bool tall = false;
    BSTNode *bt1 = nullptr;
    // 测试LL型
    cout << "LL:" << endl;
    insertAVL(bt1, 12, tall);
    BFT(bt1);
    insertAVL(bt1, 11, tall);
    BFT(bt1);
    insertAVL(bt1, 10, tall);
    BFT(bt1);

    // 测试LR型
    cout << "LR:" << endl;
    BSTNode *bt2 = nullptr;
    tall = false;
    insertAVL(bt2, 12, tall);
    BFT(bt2);
    insertAVL(bt2, 10, tall);
    BFT(bt2);
    insertAVL(bt2, 11, tall);
    BFT(bt2);

    // 测试RR
    cout << "RR:" << endl;
    BSTNode *bt3 = nullptr;
    tall = false;
    insertAVL(bt3, 10, tall);
    BFT(bt3);
    insertAVL(bt3, 12, tall);
    BFT(bt3);
    insertAVL(bt3, 13, tall);
    BFT(bt3);
    // 测试RL
    cout << "RL:" << endl;
    BSTNode *bt4 = nullptr;
    tall = false;
    insertAVL(bt4, 10, tall);
    BFT(bt4);
    insertAVL(bt4, 12, tall);
    BFT(bt4);
    insertAVL(bt4, 11, tall);
    BFT(bt4);

    // 综合测试
    BSTNode *bstree = nullptr;
    tall = false;
    cout << "测试：13, 24, 37, 90, 53"<< endl;
    insertAVL(bstree, 13, tall);
    BFT(bstree);
    insertAVL(bstree, 24, tall);
    BFT(bstree);
    insertAVL(bstree, 37, tall);
    BFT(bstree);
    insertAVL(bstree, 90, tall);
    BFT(bstree);
    insertAVL(bstree, 53, tall);
    BFT(bstree);
}