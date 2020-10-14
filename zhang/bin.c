#include <stdio.h>
#include <stdlib.h>
#include <float.h>
/*
num是要展示的float数,bin是保存所有二进制位的数组
*/
void getFloatBin(float num, char bin[])
{
    int t = 1;              //用来按位与操作
    int *f = (int *)(&num); //将float的解释成int，即float的地址转成int*
    for (int i = 0; i < 32; i++)
    {
        //从最高位开始按位与，如果为1，则bin[i]=1，如果为0，则bin[i]=0
        //这里没有将bin存成字符，而是数字1 0
        bin[i] = (*f) & (t << 31 - i) ? 1 : 0;
    }
}
int main()
{
    float test = FLT_MAX;
    char c[32];
    printf("测试float数为:%f\n", test);
    printf("二进制表示为:");
    getFloatBin(test, c);
    for (int i = 0; i < 32; i++)
    {
        printf("%d", c[i]);
        if (i == 0)
            printf(", ");
        if (i == 8)
            printf(", ");
    }
}