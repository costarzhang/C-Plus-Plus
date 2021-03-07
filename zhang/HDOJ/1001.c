#include <stdio.h>
/*
int main()
{
    int n, sum, i;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        for (i = 1; i <= n; i++)
        {
            sum += i;
        }
        printf("%d\n\n", sum);
    }
    return 0;
}
*/

int main()
{
    int n, i, sum;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        if (n % 2 == 0)
            sum = n / 2 * (n + 1);
        else
            sum = (n + 1) / 2 * n;
        printf("%d\n\n", sum);
    }
    return 0;
}