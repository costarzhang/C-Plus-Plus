#include <iostream>
#include <list>
using namespace std;

#define maxsize 20
/*树的性质
    1.树中结点数等于所有结点度数之和加1
    2.度为m的树中第i层至多有m^(i-1)
    3.高度为h的m叉树至多有(m^h-1)/(m-1)个结点
    4.具有n个结点的m叉树的最小高度是上取整( logm( n(m-1)+1 ) )
*/

/*二叉树
    满二叉树
    一颗高度为h的满二叉树含有2^h-1个结点
    完全二叉树
    按从右至左，从上到下的顺序删除一颗满二叉树的部分结点得到一颗完全二叉树
                                1
                             /    \
                            2      3
                          /  \    /  \
                        4     5   6   7
                       / \   / \  /
                      8   9 10 11 12
------------------------------------------------------
                                1
                             /    \
                            2      3
                          /  \    /  \
                        4     5   6   7
                       / \   / \  
                      8   9 10 11
叶子结点只会出现在最下面两层
若有度为1的结点，则只会有1个，且该结点只有左孩子

二叉排序树
左小右大

二叉树的性质
    1.非空二叉树中叶子结点数等于度为2的结点数加1
    2.非空二叉树第k层至多有2^(k-1)个结点
    3.高度为h的二叉树至多有2^h - 1个结点
    4.具有n个结点的完全二叉树高度为上取整( log2( n +1 ) ) 或者下取整( log2( n ) ) + 1
*/

// 孩子存储结构
typedef struct BTNode
{
    unsigned int weight; // 结点权值
    char data;
    struct BTNode *left;   // 左孩子
    struct BTNode *right;  // 右孩子
    struct BTNode *parent; // 双亲
    // 线索化标记
    int ltag = 0; // 前驱
    int rtag = 0; // 后继
} BTNode;

// 插入结点
void insert(BTNode *curr, BTNode *bt, char data, char pos)
{
    if (bt != nullptr)
    { // curr指向的树存在左右子树，则进一步将结点插入到curr的左右子树中
        char p;
        cout << "插入的结点" << data << "在" << bt->data << "的左子树还是右子树: ";
        cin >> p;
        if (p == 'l')
        { // 在curr的左子树中插入结点
            insert(bt, bt->left, data, p);
        }
        else if (p == 'r')
        { // 在curr的左子树中插入结点
            insert(bt, bt->right, data, p);
        }
    }
    else
    {
        BTNode *node = new BTNode;
        node->data = data;
        node->left = node->right = nullptr;
        if (pos == 'l')
        {
            curr->left = node;
        }
        else if (pos == 'r')
        {
            curr->right = node;
        }
        node->parent = curr; // 链接双亲结点
    }
}

// 创建二叉树
BTNode *createBTree()
{
    // 建立根结点
    char value;
    BTNode *root = new BTNode;
    cout << "输入根结点信息 :";
    cin >> value;
    root->data = value;
    root->left = root->right = nullptr;
    root->parent = nullptr;
    char p; // 结点位置（l,左子树；r，右子树）
    char data;
    cout << "插入结点的值: ";
    cin >> data;
    while (data != '#')
    { //向树中插入结点
        cout << "插入的结点" << data << "在" << root->data << "(根结点)的左子树还是右子树: ";
        cin >> p;

        if (p == 'l')
        { // 在bt的左子树中插入结点
            insert(root, root->left, data, p);
        }
        else if (p == 'r')
        { // 在bt的左子树中插入结点
            insert(root, root->right, data, p);
        }
        cout << "插入结点的值: ";
        cin >> data;
    }
    return root;
}

// 层序遍历(队列)
void BFT(BTNode *bt)
{
    list<BTNode *> queue;
    queue.push_back(bt); // 将根结点入队
    while (!queue.empty())
    {
        bt = queue.front();       // 取栈顶结点
        cout << bt->data << "  "; // 访问
        queue.pop_front();        // 将访问过的结点出队
        if (bt->left != NULL)     // 将访问过的结点的左右孩子入对
            queue.push_back(bt->left);
        if (bt->right != NULL)
            queue.push_back(bt->right);
    }
}

// 先序遍历（递归）
void Pre(BTNode *bt)
{
    if (bt != nullptr)
    {
        cout << bt->data << " "; // 现需遍历根结点
        Pre(bt->left);           // 先序遍历左子树
        Pre(bt->right);          // 先序遍历右子树
    }
}
// 先序遍（ 非递归）
void pre(BTNode *bt)
{
    BTNode *p = nullptr;
    BTNode *stack[maxsize]; // 定义辅助栈
    int top = -1;
    stack[++top] = bt; // 将根结点入栈
    while (top != -1)
    {
        p = stack[top--];
        cout << p->data << " "; // 栈顶结点出栈并访问
        if (p->right != nullptr)
        { // 当前结点右孩子入栈
            stack[++top] = p->right;
        }
        if (p->left != nullptr)
        { // 当前结点左孩子入栈
            stack[++top] = p->left;
        }
    }
}

// 求树的深度
int getDepth(BTNode *bt)
{
    BTNode *queue[maxsize]; // 队列
    BTNode *p;
    int rear;  // 队尾指针
    int front; // 队头指针
    rear = front = 0;
    int size = 0; //队列长度

    int len = 0; // 同层节点数
    int depth;   // 树的深度

    // 根结点入队
    rear = (rear + 1) % maxsize;
    queue[rear] = bt;
    size++;

    while (rear != front)
    { // 每趟循环中队列中结点为同层结点

        len = size;
        depth++;
        while (len--)
        { //访问同层结点
            front = (front + 1) % maxsize;
            p = queue[front]; // 队头结点出队
            --size;
            // 将下层结点入队
            if (p->left != nullptr)
            {
                rear = (rear + 1) % maxsize;
                queue[rear] = p->left;
                size++;
            }
            if (p->right != nullptr)
            {
                rear = (rear + 1) % maxsize;
                queue[rear] = p->right;
                size++;
            }
        }
    }
    return depth;
}

// 中序遍历递归
void In(BTNode *bt)
{
    if (bt != nullptr)
    {
        In(bt->left);            // 中序遍历左子树
        cout << bt->data << " "; // 中序遍历根结点
        In(bt->right);           // 中序遍历右子树
    }
}

// 中序遍历（非递归）
void in(BTNode *bt)
{
    BTNode *p = nullptr;
    BTNode *stack[maxsize]; // 定义辅助栈
    int top = -1;

    p = bt;
    while (top != -1 || p != nullptr)
    {
        while (p != nullptr) // 从根结点开始向左下各结点入栈
        {
            stack[++top] = p;
            p = p->left;
        }
        if (top != -1)
        {
            p = stack[top--];
            cout << p->data << " "; // 栈顶结点出栈并访问
            p = p->right;           // 到p的右子树中遍历
        }
    }
}
// 后序遍历（递归）
void Post(BTNode *bt)
{
    if (bt != NULL)
    {
        Post(bt->left);          // 后序遍历左子树
        Post(bt->right);         // 后序遍历右子树
        cout << bt->data << " "; // 后序遍历根结点
    }
}

// 后序遍历（非递归）
void post(BTNode *bt)
{
    BTNode *stack[maxsize];
    int top = -1;
    BTNode *printStack[maxsize]; // 该栈用于辅助输出
    int print = -1;

    BTNode *p;
    stack[++top] = bt; // 根结点入栈
    while (top != -1)
    {
        p = stack[top--];
        printStack[++print] = p; // 栈顶结点出栈并压入输出辅助栈
        if (p->left != nullptr)
        { // 左孩子入栈
            stack[++top] = p->left;
        }
        if (p->right != nullptr)
        { // 右孩子入栈
            stack[++top] = p->right;
        }
    }
    // 顺序输出输出辅助栈的栈中结点
    while (print != -1)
    {
        cout << printStack[print--]->data << " ";
    }
}

// 中序线索化
// curr 为当前访问结点 pre为curr的前驱
void inThread(BTNode *curr, BTNode *&pre)
{
    if (curr != nullptr)
    {
        inThread(curr->left, pre); // 对左子树进行线索化(中序遍历左子树)
        cout << "当前访问结点为: " << curr->data << " 其前驱为: " << pre->data << endl;
        if (curr->left == nullptr)
        {                     // 当前结点左指针为空，建立当前结点的前驱线索
            curr->left = pre; // 前驱线索
            curr->ltag = 1;   // 线索标记
        }
        if (pre->data != '#' && pre->right == nullptr)
        {                      // 当前访问结点的前驱结点右指针为空，建立其后继
            pre->right = curr; // 后继线索
            pre->rtag = 1;     // 线索标记
        }
        pre = curr;          // 前驱指针移动
        curr = curr->right;  // 当前访问指针移动，其前驱为pre
        inThread(curr, pre); // 对右边子树线索化
    }
}
// 中序线索化
void createinThread(BTNode *bt)
{
    BTNode *pre = new BTNode;
    BTNode *head = pre; // 记录头结点
    // 虚设头结点
    pre->data = '#';
    pre->left = bt;
    pre->right = nullptr;
    if (bt != nullptr)
    {
        inThread(bt, pre);
    }
    pre->right = head;
    pre->rtag = 1; // 为最后一个结点建立后继线索
    head->right = pre;
    head->rtag = 1;
}
// 线索化遍历
void Inorder(BTNode *bt)
{
    BTNode *p = bt;
    while (p->data != '#')
    { // 结束标志：到达虚设头节点
        while (p->ltag == 0)
        { // 向左下寻找第一个结点
            p = p->left;
        }
        cout << p->data << " ";
        while (p->rtag == 1 && p->right->data != '#')
        { // 根据后继线索向后移动实现线性遍历
            p = p->right;
            cout << p->data << " ";
        }
        p = p->right; // p的右孩子要么是后继线索要么是其右孩子，
                      // 在中序遍历中一个结点如果有右孩子，
                      // 则它的右孩子就是它的后继
    }
}

// 前序线索化
void preThread(BTNode *curr, BTNode *&pre)
{
    if (curr != nullptr)
    {
        cout << "当前访问结点为: " << curr->data << " 其前驱为: " << pre->data << endl;
        if (curr->left == nullptr)
        {
            curr->left = pre;
            curr->ltag = 1;
        }
        if (pre != nullptr && pre->right == nullptr)
        {
            pre->right = curr;
            pre->rtag = 1;
        }
        pre = curr;
        if (curr->ltag == 0)
        {
            preThread(curr->left, pre);
        }
        if (curr->rtag == 0)
        {
            preThread(curr->right, pre);
        }
    }
}
// 建立前序线索二叉树
void createpreThread(BTNode *bt)
{
    BTNode *pre = new BTNode;
    BTNode *s = pre;
    pre->data = '#';
    pre->left = nullptr;
    pre->right = bt;
    if (bt != nullptr)
    {
        preThread(bt, pre);
    }
    pre->right = s;
    pre->rtag = 1;
}
// 遍历前序线索二叉树
void Preorder(BTNode *bt)
{
    BTNode *p = bt;
    while (p->data != '#')
    { // 结束标志：到达虚设头节点
        while (p->ltag == 0)
        { // p有左孩子， 则其左孩子一定是其后继
            cout << p->data << " ";
            p = p->left;
        }
        cout << p->data << " "; // p无左孩子，则其右孩子一定是其后继，若其无右孩子的其右指针一定指向后继
        p = p->right;
    }
}

// 后序线索化
void postThread(BTNode *curr, BTNode *&pre)
{
    if (curr != nullptr)
    {

        postThread(curr->left, pre);
        postThread(curr->right, pre);
        cout << "当前访问结点为: " << curr->data << "其前驱为: " << pre->data << endl;
        ;
        if (curr->left == nullptr)
        {
            curr->left = pre;
            curr->ltag = 1;
        }
        if (pre->data != '#' && pre->right == nullptr)
        {
            pre->right = curr;
            pre->rtag = 1;
        }
        pre = curr;
    }
}

// 建立后序线索二叉树
void createpostThread(BTNode *bt)
{
    BTNode *pre = new BTNode; // 附加头结点
    BTNode *s = pre;
    pre->data = '#';
    pre->left = nullptr;
    pre->right = nullptr;
    if (bt != nullptr)
    {
        postThread(bt, pre);
    }
}

// 遍历后序线索二叉树
void Postorder(BTNode *bt)
{
    BTNode *p = bt;
    BTNode *pre = nullptr;

    while (p->data != '#')
    {
        // 找到树最左边的结点，该结点要么是根结点（其没有左子树或者没有右子树），
        //要么是叶子结点（且为左叶子）, 此结点为后序访问序列中的第一个结点
        while (p->ltag == 0 && p->left != pre)
        {
            p = p->left;
        }
        // 访问后继,
        while (p->data != '#' && p->rtag == 1)
        {
            cout << p->data << " ";
            pre = p;
            p = p->right; // 此时p的右指针是其后继线索
        }
        // 检查p是否到达了根节点
        if (p == bt)
        {
            cout << p->data << " ";
            return;
        }
        // 右节点的后继线索是它的双亲结点
        while (p->data != '#' && p->right == pre)
        {
            cout << p->data << " ";
            pre = p;
            p = p->parent;
        }
        if (p->rtag == 0 && p->data != '#')
        {
            p = p->right;
        }
    }
}
// 清除线索
void clearThread(BTNode *bt)
{
    if (bt != nullptr)
    {
        if (bt->ltag == 1)
        {
            bt->left = nullptr;
        }
        if (bt->rtag == 1)
        {
            bt->right = nullptr;
        }
        clearThread(bt->left);
        clearThread(bt->right);
    }
}

int main()
{
    int c;
    do
    {
        cout << "\n---------------------------" << endl;
        cout << "0-结束" << endl;
        cout << "1-建立二叉树" << endl;
        cout << "2-前序遍历二叉树" << endl;
        cout << "3-中序遍历二叉树" << endl;
        cout << "4-后序遍历二叉树" << endl;
        cout << "5-层序遍历二叉树" << endl;
        cout << "6-测试前序线索二叉树" << endl;
        cout << "7-测试中序线索二叉树" << endl;
        cout << "8-测试后序线索二叉树" << endl;
        cout << "输入一个数字代表你的操作: ";
        cin >> c;
        cout << "---------------------------" << endl;
        BTNode *bt;
        switch (c)
        {
        case 1:
            bt = createBTree();
            cout << "\n建立二叉树成功，二叉树的高度为:" << getDepth(bt) << endl;
            break;
        case 2:
            cout << "\n前序遍历（递归）:" << endl;
            Pre(bt);
            cout << "\n前序遍历（非递归）:" << endl;
            pre(bt);
            break;
        case 3:
            cout << "\n中序遍历（递归）:" << endl;
            In(bt);
            cout << "\n中序遍历（非递归）:" << endl;
            in(bt);
            break;
        case 4:
            cout << "\n后序遍历（递归）:" << endl;
            Post(bt);
            cout << "\n后序遍历（非递归）:" << endl;
            post(bt);
            break;
        case 5:
            cout << "\n层序遍历:" << endl;
            BFT(bt);
            break;
        case 6:
            clearThread(bt);
            cout << "\n创建前序线索树:" << endl;
            createpreThread(bt);
            cout << "\n前序线索树遍历:" << endl;
            Preorder(bt);
            break;
        case 7:
            clearThread(bt);
            cout << "\n创建中序线索树:" << endl;
            createinThread(bt);
            cout << "\n中序线索树遍历:" << endl;
            Inorder(bt);
            cout << endl
                 << bt->left->left->left->data << endl;
            break;
        case 8:
            clearThread(bt);
            cout << "\n创建后序线索二叉树:" << endl;
            createpostThread(bt);
            cout << "\n后序线索树遍历:" << endl;
            Postorder(bt);
            break;
        default:
            break;
        }
    } while (c != 0);
}