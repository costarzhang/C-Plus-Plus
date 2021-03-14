#include <stdio.h>
#include <stdarg.h>
/*c运算符（优先级从高到低）

++（后缀）--（后缀） ()（函数调用）[] {}           ->
++（前缀）--（前缀）+ ~ ! * & sizeof _Alignof()    <-
* / %                                              ->
+ -                                                ->
<< >>                                              ->
< > <= >=                                          ->
== !=                                              ->
&                                                  -> 
^                                                  ->
|                                                  ->
&&                                                 ->
||                                                 ->
?:                                                 ->
=（赋值）*= /= += -= <<= >>= &= |= ^=              ->
,                                                  ->
*/
void fun(int x, ...)
{
    va_list ap;
    va_start(ap, x);
    int y = va_arg(ap, int);
    float z = va_arg(ap, double);
    printf("%d %f\n", y, z);
    va_end(ap); //清理
}

int main()
{
    int x = 2;
    int y = 1;
    float z = 2.0f;
    fun(x, y, z);
}