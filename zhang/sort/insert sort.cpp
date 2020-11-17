#include <iostream>
using namespace std;
/**
 * 插入类排序
 * 1.直接插入排序 o(n^2) o(1)
 * 2.折半插入排序 o(nlog2n) o(1)
 * 3.希尔排序     o(n^2)-o(n^1.3) o(1)
 */
void print(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
}
// 直接插入排序
/**
 * 将待排序序列分成两部分，在有序序列中查找待排序序列第一个元素的插入位置，
 * 找到移动有序元素，将元素插入
 */
void insertsort(int A[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        if (A[i] < A[i - 1])
        {
            temp = A[i];
            for (j = i - 1; temp < A[j]; --j)
            {
                A[j + 1] = A[j];
            }
            A[j + 1] = temp;
        }
    }
}

void binaryinsertsort(int A[], int n)
{
    int i, j, low, high, mid;
    int temp;
    for (i = 1; i < n; i++) // 无序序列默认从第二个记录开始
    {
        temp = A[i];
        low = 0;
        high = i - 1;
        // 在有序序列中折半查找插入位置
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (temp < A[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (j = i - 1; j >= high + 1; --j)
        {
            A[j + 1] = A[j];
        }
        A[high + 1] = temp;
    }
}

// shell排序
void shellsort(int A[], int n)
{
    int dk; //增量
    int i;
    int j;
    int temp;
    for (dk = n / 2; dk >= 1; dk = dk / 2) // 增量每次减为一半
    {
        for (i = dk + 1; i <= n; i++)
        {
            if (A[i] < A[i - dk]) //检查位于同一个子表中的记录
            {
                temp = A[i];
                for (j = i - dk; j >= 0 && temp < A[j]; j -= dk)
                {
                    A[j + dk] = A[j];
                }
                A[j + dk] = temp;
            }
        }
    }
}
int main()
{
    int A[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    //insertsort(A, 10);
    //binaryinsertsort(A, 10);
    shellsort(A, 10);
    print(A, 10);
    return 0;
}