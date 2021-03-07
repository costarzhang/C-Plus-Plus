#include <stdio.h>

// 递归
void printOut(unsigned int N)
{
    if (N > 10)
        printOut(N / 10);
    printf("%d", N % 10);
}
int main()
{

    return 0;
}