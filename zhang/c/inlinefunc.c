#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
inline static void fun(void)
{
    printf("内联函数！\n");
}
_Noreturn void print()
{
    printf("不返回主调函数\n");
    return;
}
#define SORT(x) _Generic((x), double   \
                         : sqrt, float \
                         : fun)(x)

int comp(const void *p, const void *q)
{
    const double *d = (const double *)p;
    const double *e = (const double *)q;
    if (*d < *e)
        return -1;
    else if (*d == *e)
        return 0;
    else
        return 1;
}
int main()
{
    //fun();
    //print();
    //atexit(fun);
    /*
    double x = 81.0;
    float xx = 9.0f;
    printf("%lf\n", SORT(x));
    SORT(xx);*/
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    qsort(a, 10, sizeof(int), comp);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    memcpy();
    memmove();
    exit(0);
    return 0;
}