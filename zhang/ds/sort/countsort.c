#include <stdio.h>

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

void countsort(int a[], int c[], int r[])
{
    for (int i = 0; i < 6; i++)
        c[i] = 0;
    for (int i = 0; i < 8; i++)
        c[a[i]]++;
    print(c, 6);
    for (int i = 1; i < 6; i++)
        c[i] += c[i - 1];
    print(c, 6);
    for (int i = 0; i < 8; i++)
    {

        r[c[a[i]] - 1] = a[i];
        c[a[i]]--;
    }
}

int main()
{
    int a[8] = {4, 5, 0, 3, 1, 5, 0, 5};
    int r[8], c[6];
    countsort(a, c, r);
    print(r, 8);
}