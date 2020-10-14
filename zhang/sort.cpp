#include <iostream>
using namespace std;
void output(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int setPartition(int a[], int n) {
    int piovtkey; // 枢轴值
    int low = 0, low0 = 0;
    int high = n-1, high0 = n-1;

    int flag = 1;
    int k = n / 2;
    int i;

    while (flag) {
        piovtkey = a[low];
        cout << low << "枢轴值" << piovtkey << endl;
        while (low < high) {
            while (low < high && a[high] >= piovtkey)
            {
                --high;
            }
            if (low != high) {
                a[low] = a[high]; // 找到一个比枢轴小的值
            }
            cout << "low: " << low << " high: " << high << "  ";
            output(a, n);
            while (low < high && a[low] <= piovtkey)
            {
                ++low;
            }
            if (low != high) {
                a[high] = a[low]; // 找到一个比枢轴大的值
            }
            cout << "low: " << low << " high: " << high << "  ";
            output(a, n);
            cout << endl;
        }

        a[low] = piovtkey; // 枢轴值放到最终位置
        cout << "**************************" << endl;
        output(a, n);
        if (low == k - 1)
        {
            flag = 0;
        } else {
            if (low < k - 1)
            {
                low0 = ++low;
                high = high0;
            }else {
                high0 = --high;
                low = low0;
            }
        }
    }
    int s1, s2;
    for (i = 0; i < k; i++) {
        s1 += a[i];
    }
    for (i = k; i < n; i++) {
        s2+= a[i];
    }
    return s2-s1;
}
int main() {
    int a[7] = {7, 1, 5, 2, 4, 3, 6};
    setPartition(a, 7);
}