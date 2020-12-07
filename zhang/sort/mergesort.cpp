#include <iostream>
using namespace std;

void merge(int a[], int low, int mid, int high, int n)
{
    int *b = (int *)malloc(n * sizeof(int));
    for (int i = low; i <= high; i++)
    {
        b[i] = a[i];
    }
    int i, j, k;
    //归并
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
    {
        if (b[i] < b[j])
        {
            a[k] = b[i++];
        }
        else
        {
            a[k] = b[j++];
        }
    }
    while (i <= mid)
        a[k++] = b[i++];
    while (j <= high)
        a[k++] = b[j++];
}

void mergesort(int a[], int low, int high, int n)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(a, low, mid, n);
        mergesort(a, mid + 1, high, n);
        merge(a, low, mid, high, n);
    }
}

int main()
{
    int a[7] = {49, 38, 65, 97, 76, 13, 27};
    mergesort(a, 0, 6, 7);
    for (int i = 0; i < 7; i++)
    {
        cout << a[i] << " ";
    }
}