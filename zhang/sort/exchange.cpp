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
    cout << endl;
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
/*
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
    print(A, 10);
    cout << endl;
    quicksort(A, left, ileft - 1); // 递归
    quicksort(A, ileft + 1, right);
}
*/
// 快速排序
void quicksort(int A[], int left, int right)
{
    int ileft, iright; //左右哨兵
    int pivot;
    ileft = left;
    iright = right;
    pivot = A[left];

    if (left < right)
    {
        while (ileft < iright)
        {
            // 从右向找到一个比基准值小的记录
            while (A[iright] >= pivot && ileft < iright)
            {
                iright--;
            }
            if (ileft < iright)
            {
                A[ileft] = A[iright];
                ileft++;
            }
            //从左向右找到一个比基准值大的记录
            while (A[ileft] <= pivot && ileft < iright)
            {
                ileft++;
            }
            if (ileft < iright)
            {
                A[iright] = A[ileft];
                iright--;
            }
        }
        // 基准值归位
        A[ileft] = pivot;
        print(A, 10);
        cout << endl;
        quicksort(A, left, ileft - 1); // 递归
        quicksort(A, ileft + 1, right);
    }
}
//双向冒泡排序
void bubblesortb(int a[], int n)
{
    int left = 0, right = n - 1;
    int flag;
    while (left < right)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                flag = 1;
            }
        }
        if (!flag)
            break;
        right--;
        for (int j = right; j > left; j--)
        {
            if (a[j] < a[j - 1])
            {
                swap(a[j], a[j - 1]);
                flag = 1;
            }
        }
        if (!flag)
            break;
        left++;
        print(a, n);
    }
}
int main()
{
    int A[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    bubblesortb(A, 10);
    print(A, 10);
    return 0;
}