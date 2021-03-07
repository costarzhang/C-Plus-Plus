#include <stdio.h>
int main()
{
    int n, i, j, a;
    int sum;
    scanf("%d", &n);
    while (n--)
    {
        sum = 0;
        scanf("%d", &i);
        for (j = 0; j < i; j++)
        {
            scanf("%d", &a);
            sum += a;
        }
        if (n != 0)
            printf("%d\n\n", sum);
        else
            printf("%d\n", sum);
    }
}