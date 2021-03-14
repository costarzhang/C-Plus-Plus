#include <stdio.h>
#include "liststatic.h"
int main()
{
    InitializeCursorSpace();
    CursorAlloc();
    char a = 'a';
    for (int i = 0; i < SpaceSize - 2; i++)
    {
        Insert(a, 0, i + 1);
        a++;
    }
    Delete('b', 1);
    printl(1);
    Insert('b', 1, 2);
    printl(1);
    return 0;
}
