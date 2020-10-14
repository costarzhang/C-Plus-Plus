#include <iostream>
using namespace std;

void selectsort(int a[], int n) {
    int i, j, t;
    int min;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
        }
        if (min != i) {
            t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
    }
}

int main() {
    int a[10] = {8, 3, 9, 11, 2, 1, 4, 7, 5, 10};
    selectsort(a, 10);

    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
}