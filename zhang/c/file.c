#include <stdio.h>
#include <stdlib.h>
/*文件操作相关函数
fopen(filename,mode) getc(stream) putc(char,stream) exit() fclose()
fprintf() fscanf() fgets() fputs()
rewind() fseek() ftell() fflush()
fgetpos() fsetpos() feof() ferror()
ungetc() setvbuf() fread()
*/
int main(int argc, char **argv)
{
    int i[1] = {8};
    int a[3];
    FILE *fp;
    fp = fopen("test", "a");
    //fprintf(fp,"%d",i[0]);
    fwrite(i, sizeof(int), 1, fp);
    FILE *f = fopen("test", "r");
    fread(a, sizeof(int), 1, f);
    printf("%d\n", a[0]);
    return 0;
}

