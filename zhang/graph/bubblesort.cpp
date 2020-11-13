#include <iostream>
using namespace std;
void display(int a[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
void bubblesort(int a[], int n)
{
    int i, j;
    int flag = 0;

    for (j = 1; j <= n; j++)
    {
        flag = 0;
        for (i = 1; i <= j; i++)
        {
            if (a[i] > a[i + 1])
            {
                a[0] = a[i];
                a[i] = a[i + 1];
                a[i + 1] = a[0];
                flag = 1;
            }
            if (!flag)
                break;
        }
    }
}

int main()
{
    int a[6] = {999, 5, 4, 3, 2, 1};
    int i, j;
    int flag = 0;

    for (j = 5; j >= 1; j)
    {
        flag = 0;
        for (i = 1; i <= j - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                a[0] = a[i];
                a[i] = a[i + 1];
                a[i + 1] = a[0];
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
    display(a, 5);
}