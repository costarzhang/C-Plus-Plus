#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
    int a;
    int b;
    int c;
};

typedef struct triangle triangle;

double get_area(triangle tr)
{
    int p = (tr.a + tr.b + tr.c) / 2;
    return sqrt(p * abs(p - tr.a) * abs(p - tr.b) * abs(p - tr.c));
}
void sort_by_area(triangle *tr, int n)
{
    /**
    * Sort an array a of the length n
    */
    double areas[n];
    for (int i = 0; i < n; i++)
    {
        areas[i] = get_area(tr[i]);
    }
    for (int i = 1; i < n; i++)
    {
        double key = areas[i];
        int a = tr[i].a;
        int b = tr[i].b;
        int c = tr[i].c;
        int j = i - 1;
        while (j >= 0 && areas[j] > key)
        {
            areas[j + 1] = areas[j];
            tr[j + 1].a = tr[j].a;
            tr[j + 1].b = tr[j].b;
            tr[j + 1].c = tr[j].c;
            j -= 1;
        }
        areas[j + 1] = key;
        tr[j + 1].a = a;
        tr[j + 1].b = b;
        tr[j + 1].c = c;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    triangle *tr = (triangle *)malloc(n * sizeof(triangle));
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    }
    sort_by_area(tr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}