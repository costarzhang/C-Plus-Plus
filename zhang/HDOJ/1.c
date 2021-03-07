#include <stdio.h>

int main()
{
    int n;
    while (scanf("%d", &n) != -1)
    {
        if (n >= 0)
        {
            int z[50000] = {1}, i, j, c, m = 1;
            for (j = n + 1; --j; m = i)
                for (c = 0, i = -1; ++i < m || c; c /= 10)
                    z[i] = (c += z[i] * j) % 10;
            while (printf("%d", z[--m]), m)
                ;
            printf("\n");
        }
    }
    return 0;
}
