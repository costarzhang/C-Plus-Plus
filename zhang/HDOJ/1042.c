#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void sum(char A[], char B[])
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
        B[k] = base + '0';
    }
    if (k < i)
    {
        for (; k < i; k++)
        {
            base = (A[k] - '0' + carry) % 10;
            carry = (A[k] - '0' + carry) / 10;
            B[k] = base + '0';
        }
    }
    if (k < j)
    {
        for (; k < j; k++)
        {
            base = (B[k] - '0' + carry) % 10;
            carry = (B[k] - '0' + carry) / 10;
            B[k] = base + '0';
        }
    }
    if (carry)
    {
        B[k] = carry + '0';
    }
    reverse(A);
    reverse(B);
}
void mul(char a[], char b[], char re[])
{
    int carry = 0, base, i, j, k;
    char temp[36000] = {'0'};
    int lena = strlen(a);
    int lenb = strlen(b);
    reverse(a);
    reverse(b);
    for (i = 0; i < lena; i++)
    {
        char c[10001];
        for (j = 0; j < lenb; j++)
        {
            base = ((a[i] - '0') * (b[j] - '0') + carry) % 10;
            carry = ((a[i] - '0') * (b[j] - '0') + carry) / 10;
            c[j] = base + '0';
        }
        if (carry)
        {
            c[j++] = carry + '0';
            carry = 0;
        }
        for (k = j; k < j + i; k++)
        {
            c[k] = '0';
        }
        reverse(c);
        sum(c, temp);
    }
    reverse(temp);
    strcpy(re, temp);
}
int main()
{
    int n;
    char a[10001];
    while (scanf("%d", &n) != EOF)
    {
        char r[36000] = {'1'};
        for (int i = 1; i <= n; i++)
        {
            itoa(i, a, 10);
            mul(a, r, r);
        }
        reverse(r);
        printf("%s\n", r);
    }
    /*
    char a[10001], b[10001], c[10001];
    scanf("%s%s", a, b);
    mul(a, b, c);
    reverse(c);
    printf("%s", c);*/
}