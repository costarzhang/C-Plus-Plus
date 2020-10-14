#include <iostream>
using namespace std;
void insertsort(int a[], int n) {
    int flag;
    int i, j;
    for (i = 1; i < n; i++) {
        if (a[i] < a[i-1]) {
            flag = a[i];
            for (j = i - 1; flag < a[j] && j >=0; j--) {
                a[j+1] = a[j];
            }
            a[j+1] = flag;
        }
    }

    for (int k = 0; k < 10; k++) {
        cout << a[k] << " ";
    }cout << endl;
}

int main() {
    int a[10] = {8, 3, 9, 11, 2, 1, 4, 7, 5, 10};
    insertsort(a, 10);
}