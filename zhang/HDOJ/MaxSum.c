#include <stdio.h>
/*
int MaxSubsequence(const int A[], int N)
{
    int TempSum, MaxSum, i, j, k;
    MaxSum = 0;
    for (i = 0; i < N; i++)
    {
        for (j = i; j < N; j++)
        {
            TempSum = 0;
            for (k = i; k <= j; k++)
                TempSum += A[k];
            if (TempSum > MaxSum)
                MaxSum = TempSum;
        }
    }
    return MaxSum;
}*/

int MaxSubsequence(const int A[], int N)
{
    int TempSum, MaxSum, i, j, k;
    MaxSum = 0;
    for (i = 0; i < N; i++)
    {
        TempSum = 0;
        for (j = i; j < N; j++)
        {
            TempSum += A[j];
            if (TempSum > MaxSum)
                MaxSum = TempSum;
        }
    }
    return MaxSum;
}
int max(int a, int b, int c)
{
    int max;
    max = a >= b ? a : b;
    return max >= c ? max : c;
}
int mseq(const int a[], int left, int right)
{
    int maxleftsum, maxrightsum;             //左右部分的最大子序列和
    int maxleftbordersum, maxrightbordersum; //跨越左右两边的最大和
    int leftbordersum, rightbordersum;
    int center, i;

    if (left == right) //简单情形，子序列仅有一个元素
        if (a[left] > 0)
            return a[left];
        else
            return 0;
    center = (left + right) / 2;
    maxleftsum = mseq(a, left, center);
    maxrightsum = mseq(a, center + 1, right);

    maxleftbordersum = 0;
    leftbordersum = 0;
    for (i = center; i >= left; i--)
    {
        leftbordersum += a[i];
        if (leftbordersum > maxleftbordersum)
            maxleftbordersum = leftbordersum;
    }
    maxrightbordersum = 0;
    rightbordersum = 0;
    for (i = center + 1; i <= right; i++)
    {
        rightbordersum += a[i];
        if (rightbordersum > maxrightbordersum)
            maxrightbordersum = rightbordersum;
    }
    return max(maxleftsum, maxrightsum, maxleftbordersum + maxrightbordersum);
}
int mseq(const int a[], int n)
{
    int tempsum, maxsum, i;
    tempsum = maxsum = 0;
    for (i = 0; i < n; i++)
    {
        tempsum += a[i];
        if (tempsum > maxsum)
            maxsum = tempsum;
    }
    return maxsum;
}
#include <stdio.h>
int main()
{
    int c;
    scanf("%d", &c);
    while (c--)
    {
        int n;
        int a[1000001];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        int TempSum, MaxSum, i, j, k;
        MaxSum = 0;
        int left, right;
        for (i = 0; i < n; i++)
        {
            TempSum = 0;
            for (j = i; j < n; j++)
            {
                TempSum += a[j];
                if (TempSum > MaxSum)
                {
                    MaxSum = TempSum;
                    left = i;
                    right = j;
                }
            }
        }
        printf("%d %d %d\n", MaxSum, left, right);
    }
}