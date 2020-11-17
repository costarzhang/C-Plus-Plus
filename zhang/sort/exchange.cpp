/**
 * 交换类排序
 * 1.冒泡排序
 * 2.快速排序
 */

#include <iostream>
using namespace std;

void print(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void sort(int A[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[i])
            {
                swap(A[j], A[i]);
            }
        }
    }
}

// 快速排序
void quicksort(int A[], int left, int right)
{
    int ileft, iright; //左右哨兵
    int pivot;
    if (left > right)
    {
        return;
    }
    ileft = left;
    iright = right;
    pivot = A[left];

    while (ileft != iright)
    {
        // 从右向找到一个比基准值小的记录
        while (A[iright] >= pivot && ileft < iright)
        {
            iright--;
        }
        //从左向右找到一个比基准值大的记录
        while (A[ileft] <= pivot && ileft < iright)
        {
            ileft++;
        }
        if (ileft < iright) // 交换两个元素
        {
            swap(A[ileft], A[iright]);
        }
    }
    // 基准值归位
    A[left] = A[ileft];
    A[ileft] = pivot;
    quicksort(A, left, ileft - 1); // 递归
    quicksort(A, ileft + 1, right);
}

int main()
{
    int A[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    quicksort(A, 0, 9);
    print(A, 10);
    return 0;
}