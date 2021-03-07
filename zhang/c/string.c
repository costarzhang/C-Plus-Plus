#include <stdio.h>
#include <stdlib.h>
#define STLEN 81
int main()
{
    /*atoi()*/
    char words[STLEN];
    puts("Enter a string");
    //fgets(words, 10, stdin);
    //gets(words);//丢弃换行符
    //puts(words);
    //fputs(words, stdout);//不添加换行符
    sprintf(words, "%s,%+10s%s\n", "WWWW", "Hello", "jjj");
    puts(words);
}