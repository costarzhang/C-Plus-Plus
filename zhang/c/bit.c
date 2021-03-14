#include <stdio.h>
#include <limits.h>
#define TYPE int
/*c位运算
~按位取反
&按位与
|按位或
^按位异或
<<左移
>>右移
*/
char *itobs(int, char *);
char *ftobs(float, char *);
char *dtobs(double, char *);
int main()
{
    int x;
    scanf("%d", &x);
    char bin_str[CHAR_BIT * sizeof(TYPE) + 1];
    char bin_str1[CHAR_BIT * sizeof(TYPE) + 1];
    //itobs(x, bin_str);
    //dtobs(x, bin_str);
    itobs(x, bin_str);
    puts(bin_str);
    x <<= 1;
    itobs(x, bin_str1);
    puts(bin_str1);
    return 0;
}
char *itobs(int x, char *bs)
{
    int i;
    const static int size = CHAR_BIT * sizeof(int);
    for (i = size - 1; i >= 0; i--, x >>= 1)
    {
        bs[i] = (01 & x) + '0';
    }
    bs[size] = '\0';
    return bs;
}

char *ftobs(float x, char *bs)
{
    int i;
    const static int size = CHAR_BIT * sizeof(float);
    int *p;
    p = (int *)&x;
    for (i = size - 1; i >= 0; i--, (*p) >>= 1)
    {
        bs[i] = (01 & *p) + '0';
    }
    bs[size] = '\0';
    return bs;
}

char *dtobs(double x, char *bs)
{
    int i;
    const static int size = CHAR_BIT * sizeof(double);
    int *p;
    p = (int *)&x;
    for (i = size - 1; i >= 0; i--, (*p) >>= 1)
    {
        bs[i] = (01 & *p) + '0';
    }
    bs[size] = '\0';
    return bs;
}
