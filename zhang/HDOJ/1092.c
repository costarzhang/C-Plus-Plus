#include <stdio.h>
int main()
{
    int n, i;
    int sum, a;
    while (scanf("%d", &n) && n != 0)
    {
        sum = 0;
        for (i = 0; i < n; i++)
        {
            scanf("%d", &a);
            sum += a;
        }
        printf("%d\n", sum);
    }
}