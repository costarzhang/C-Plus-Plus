#include <iostream>
using namespace std;
void chage(int *p)
{
    int m;
    p = &m;
}
int main()
{
    int a = 3;

    int *p = &a;
    cout << p << endl;
    chage(p);
    cout << p;
}