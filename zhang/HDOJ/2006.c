#include <stdio.h>
int main()
{
    int n, re = 1;
    while (scanf("%d", &n) != EOF)
    {
        int d;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &d);
            if (d % 2 == 1)
                re *= d;
        }
        printf("%d\n", re);
    }
    return 0;
}