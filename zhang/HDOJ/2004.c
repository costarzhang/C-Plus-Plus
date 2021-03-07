#include <stdio.h>

int main()
{
    int s;
    while (scanf("%d", &s) != EOF)
    {
        if (s <= 100 && s >= 90)
            printf("%c\n", 'A');
        if (s <= 89 && s >= 80)
            printf("%c\n", 'B');
        if (s <= 79 && s >= 70)
            printf("%c\n", 'C');
        if (s <= 69 && s >= 60)
            printf("%c\n", 'D');
        if (s <= 59 && s >= 0)
            printf("%c\n", 'E');
        if (s < 0 || s > 100)
            printf("Score is error!\n");
    }
    return 0;
}