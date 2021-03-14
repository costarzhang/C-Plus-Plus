/*
#define fun(X, ...) __VA_ARGS__ *X
#define D(x) x##1
#define LIMITE 9
#undef LIMITE
#define LIMITE 10

#ifndef LIMITE
//#define L 90
#define L 00
#else
//#include <math.h>
#define L 87
#include <stdio.h>
#endif

#if L == 87
#define l 900
#else
#endif*/
#include <stdio.h>
#define C(x) _Generic((x), int       \
                      : "int", float \
                      : "float")
/*
#line 
#error
*/
//#pragma 编译指令
int main()
{
    int x = 3;
    /*
    x = D(2);
    printf("%d\n", x);
    printf("%d\n", LIMITE);
    printf("%d\n", L);
    printf("%d\n", l);
    printf("%d\n", __LINE__);
*/
    printf("%s\n", C(x));
    return 0;
}