#include <stdio.h>
void t(int[]);
void fun(int *, int);
int main()
{
    int *c;
    int i = 9;
    c = &i;
    void (*fp)(int *, int);
    fp = fun;
    fp(c, i);
    (*fp)(c, i);
    return 0;
}

void t(int a[])
{
    //printf("%d\n", a[0]);
    //putchar(a[0]);
    return;
}

void fun(int *p, int i)
{
    printf("%d\n", i);
}