#include <iostream>
using namespace std;

void move(int A[], int n) {
    int i = -1, temp;
    for (int j = 0; j < n; j++) {
        if (A[j] % 2 == 1) {
            ++i;
            if (i != j) {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
    }
}

int main() {
    int A[] = {1, 2, 4, 3, 7, 2, 4, 1, 1};
    move(A, 9);
    for (int i = 0; i < 9; i++) {
        cout << A[i] << "**";
    }
    cout << endl;
    getchar();
    return 0;
}