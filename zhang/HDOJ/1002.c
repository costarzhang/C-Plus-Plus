#include <stdio.h>
#include <string.h>

// 字符数组逆置
void reverse(char num[])
{
    int len = strlen(num);
    int i, temp;
    for (i = 0; i < len / 2; i++)
    {
        temp = num[i];
        num[i] = num[len - 1 - i];
        num[len - 1 - i] = temp;
    }
}

void sum(char A[], char B[], char C[])
{
    int n, i, j, k;
    int carry = 0, base = 0;
    i = strlen(A);
    j = strlen(B);
    reverse(A);
    reverse(B);
    for (k = 0; k < i && k < j; k++)
    {
        base = (A[k] - '0' + B[k] - '0' + carry) % 10;
        carry = (A[k] - '0' + B[k] - '0' + carry) / 10;
        C[k] = base + '0';
    }
    if (k < i)
    {
        for (; k < i; k++)
        {
            base = (A[k] - '0' + carry) % 10;
            carry = (A[k] - '0' + carry) / 10;
            C[k] = base + '0';
        }
    }
    if (k < j)
    {
        for (; k < j; k++)
        {
            base = (B[k] - '0' + carry) % 10;
            carry = (B[k] - '0' + carry) / 10;
            C[k] = base + '0';
        }
    }
    if (carry)
    {
        C[k++] = carry + '0';
    }
    reverse(C);
    reverse(A);
    reverse(B);
}
int main()
{

    int n, i, count = 0;
    scanf("%d", &n);
    while (n > 0)
    {
        count++;
        char A[1001] = {'0'}, B[1001] = {'0'}, C[1005] = {'0'};
        scanf("%s%s", A, B);
        sum(A, B, C);
        printf("Case %d:\n", count);
        printf("%s + %s = %s\n", A, B, C);
        if (n != 1)
        {
            printf("\n");
        }
        --n;
    }
    return 0;
}