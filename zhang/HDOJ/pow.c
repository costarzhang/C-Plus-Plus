#include <stdio.h>
/*计算x^n*/
long int pow(long int x, unsigned int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n % 2 == 0)
        return pow(x * x, n / 2);
    else
        return pow(x * x, n / 2) * x;
}