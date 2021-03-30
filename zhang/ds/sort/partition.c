#include <stdio.h>

void swap(int &a, int &b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
int partition(int a[], int start, int end)
{
    int i, j;
    int tmp, x;
    x = a[end]; //按x分割元素
    i = start - 1;
    for (j = start; j < end; j++)
    {
        if (a[j] <= x)
            swap(a[++i], a[j]);
    }
    swap(a[i + 1], a[end]);
    return i + 1;
}
void print(int a[])
{
    for (int i = 0; i < 8; i++)
        printf("%d  ", a[i]);
    printf("\n");
}
void quicksort(int a[], int start, int end)
{
    int p;
    if (start < end)
    {
        p = partition(a, start, end);
        quicksort(a, start, p - 1);
        quicksort(a, p + 1, end);
    }
}
int main()
{
    int a[8] = {3, 9, 8, 1, 5, 6, 2, 5};
    //partition(a, 0, 7);
    quicksort(a, 0, 7);
    print(a);
}