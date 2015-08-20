#include <iostream>
#include <cassert>
using namespace std;

void test ()
{
    const int a=10, b=20;
//    b=20;     /* b is const int */

    int c,d;
//    int *const pc=&c, pd=&d;   /* pd is int */
}

/* you can not define it twice */
const int val = 10;
//const int val = 10;

int main ()
{
    int v = 10;
    const int &r = v;
    v = 20;
    assert (r==20);

    /* It is ok */
    const int &rd = 3.14*v;
    assert (rd==31);
}
