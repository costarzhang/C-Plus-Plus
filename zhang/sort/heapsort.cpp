#include <iostream>

using namespace std;

// 向下调整
void adjustdown(int a[], int curr, int len)
{
    a[0] = a[curr];
    int i;
    for (i = 2 * curr; i <= len; i *= 2)
    {
        if (i < len && a[i] < a[i + 1]) // 选出待调整结点的左右孩子值较大者
            i++;
        if (a[0] >= a[i]) // 待调整结点值比其孩子结点值大，满足大根堆的定义，无需调整
            break;
        else
        {                  // 待调整结点的孩子结点中有比其大的，将待调整节点与孩子结点互换
            a[curr] = a[i]; // 将a[i]调整值其双亲的位置
                curr = i;  // 继续向下调整
        }
    }
    a[curr] = a[0];
}
// 向上调整
void adjustup(int a[], int curr) {
    a[0] = a[curr];
    int i = curr / 2; // 求得curr的双亲
    while (i > 0 && a[i] < a[0]) {
        a[curr] = a[i];
        curr = i;
        i = curr / 2;
    }
    a[curr] = a[0];
}
void display(int a[], int len) {
    for (int i = 1; i <= len; i++) {
        cout << a[i] << "  ";
    }
    cout << endl;
}
// 建堆，将一组无需元素视为一颗完全二叉树，将其调整为大根堆或者小根堆
void biudmaxheap(int a[], int len) {
    for (int i = len / 2; i > 0; i--) {
        adjustdown(a, i, len);
    }
}



void heapsort(int a[], int len) {
    biudmaxheap(a, len);
    int i;
    for (i = len; i > 1; i--) {
        cout << a[1] << "  ";
        int t = a[i];
        a[i] = a[1];
        a[1] = t;
        adjustdown(a, 1, i-1);
    }
    cout << a[1];
}
int main() {
    int heap[9] = {0, 53, 17, 78, 9, 45, 65, 87, 32};
    heapsort(heap, 8);
    return 0;
}