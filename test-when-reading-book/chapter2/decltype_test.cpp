#include <iostream>
#include <assert.h>

using namespace std;

void test1 ()
{
    int a = 3, b = 4;
    
    decltype(a) c = a;  /* int c = a */

    decltype((b)) d = a;    /* int &d = a */
    decltype(&a) xx = nullptr;    /* int * */
    ++c;
    ++d;

    assert (4 == a);
    assert (4 == b);
    assert (4 == c);
    assert (4 == d);
}
void test2 ()
{
    int a = 3, b = 4;
    decltype (a) c = a; /* int */

    decltype (a=b) d = a;   /* int &*/

    assert (3 == a);
    assert (4 == b);
    assert (3 == c);
    assert (3 == d);

    a = 100;
    assert (3 == c);
    assert (100 == d);
}

int main ()
{
    test1();
    test2();
    return 0;
}
