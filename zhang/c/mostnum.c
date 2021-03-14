#include <stdio.h>
//寻找主元素
int most(int a[], int n)
{
    if (n == 1)
        return a[0];
    if (n == 2)
    {
        if (a[0] != a[1])
            return -9999;
        else
            return a[0];
    }
    int i;
    int count = 0;
    for (i = 0; i < n / 2; i++)
        if (a[2 * i] == a[2 * i + 1])
            a[count++] = a[2 * i];
    if (n % 2 == 1)
        a[count++] = a[n - 1];
    return most(a, count);
}
int main()
{
    int a[9] = {3, 3, 4, 2, 4, 4, 2, 4};
    printf("%d\n", most(a, 8));
    return 0;
}