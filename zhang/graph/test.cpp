#include<iostream>
#include<typeinfo>
#include <math.h>
using namespace std;

#define size 10

typedef struct test
{
    int i = 0;
    int a[size];
    struct test *t;
}test;
// , test &w, test *p, test *&q
void Wtest(int i, int a[], int &x, test t) {
    i = 2;
    a[0] = 999;
    x = 3;
    t.i = 1000;
    t.a[0] = 111111;
    cout << typeid(a).name() << endl;
    cout << typeid(t).name() << endl;
}

int  main() {
   char *a = "123";
   char *b = a;
   cout << a[2];
}
