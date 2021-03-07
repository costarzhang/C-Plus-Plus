#include <stdio.h>
#include <stdlib.h>
//#include <stdatomic.h>
#include <threads.h>

double stick(double ar[restrict 20])
{
    printf("stick()\n");
    double a;
    ar[0] = a;
}

int main()
{
    volatile int v = 0;
    int a;
    int(*p)[2]; //p是一个指针，其指向的类型为数组
    p = (int(*)[2])malloc(2 * 2 * sizeof(int));
    int *q[2]; //q是一个数组其中每个元素结尾指向int型的指针
    for (int i = 0; i < 2; i++)
    {
        q[i] = (int *)malloc(2);
    }
    printf("动态数组\n");
    /*
    const int *p1;       //指针可变，值不可变
    int *const p2;       //指针不可变，值可变
    const int *const p3; //指针和值皆不可变
    int const *p4;       //指针可变，值不可变
    return 0;
    */
    double *restrict s;
    stick(s);
}