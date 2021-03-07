
#include <stdio.h>
#include <string.h>
int w = 1;               //这里的w=1代表初始只有一位
void fac(int k, int a[]) //key point：算出每一位的值然后按顺序输出即可
{
    int x = 0, i;
    for (int i = 1; i <= w; ++i)
    {
        a[i] = a[i] * k + x; //第一次进入这个循环一定是x=0，这是算出不进位时这一位的值；
        x = a[i] / 10;       //是低位向高位进位的数字
        a[i] %= 10;          //i位的数字算出来，其实是取整
    }
    while (x > 0) //如果需要进位的话
    {
        w++;           //，总位数加一，控制总位数，如果x=0的话，就意味着不需要
        a[w] = x % 10; //新进的的一位，比如60*6时，需要把360的3算出来
        x /= 10;       //这里应该一定是0
    }
}
int main()
{
    int a[100000], n;
    a[1] = 1;
    while (scanf("%d", &n))
    {
        for (int i = 1; i <= n; ++i)
            fac(i, a);
        for (int j = w; j >= 1; --j)
            printf("%d", a[j]); //输出
        printf("\n");
    }
}