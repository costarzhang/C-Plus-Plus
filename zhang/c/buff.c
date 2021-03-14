#include <stdio.h>
#include <string.h>
int main()
{
    char buff[1024];
    memset(buff, '\0', sizeof(buff));
    setvbuf(stdout, buff, _IOFBF, 1024);
    printf("l");
    //fflush(stdout);
    return 0;
}