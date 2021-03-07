#include <stdio.h>
void selectsort(char a[], int n)
{
    int i, j;
    char t;
    int min;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
        if (min != i)
        {
            t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
    }
}
int main()
{
    char a[3];
    while (scanf("%c%c%c", &a[0], &a[1], &a[2]) != EOF)
    {
        selectsort(a, 3);
        for (int i = 0; i < 2; i++)
            printf("%c ", a[i]);
        printf("%c\n", a[2]);
        scanf("%*c");
    }
    return 0;
}