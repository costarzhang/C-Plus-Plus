#include <iostream>
using namespace std;

void quicksort(int left, int right, int a[]) {
    int i, j, t, temp;
    if (left > right)
        return ;
    temp = a[left]; // 枢轴值
    i = left;
    j = right;
    while (i != j) {
        while (a[j] >= temp && i < j) // 从右向左找到一个值比枢轴值小
            j--;
        while (a[i] <= temp && i < j) // 从左往右找到一个比枢轴值大的数
            i++;
        if (i < j) {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    //枢轴值与寻找结束时（即i与j重合时的元素交换）
    a[left] = a[i];
    a[i] = temp;
    quicksort(left, i - 1, a);
    quicksort(i + 1, right, a);
}

int main() {
    int a[10] = {8, 3, 9, 11, 2, 1, 4, 7, 5, 10};
    quicksort(0, 9, a);

    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
}