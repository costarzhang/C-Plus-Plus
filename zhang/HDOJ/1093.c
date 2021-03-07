#include <stdio.h>
int main()
{
    int n, i, j;
    int sum, a;
    scanf("%d", &j);
    while (j--)
    {
        sum = 0;
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%d", &a);
            sum += a;
        }
        printf("%d\n", sum);
    }
}