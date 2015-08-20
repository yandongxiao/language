#include <vector>
#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

void right_value ()
{
    int b = 10;
    decltype(b) c = b;  /* int c = b */
    assert (&b != &c);    

    /* (b) is left value */
    decltype((b)) d = b;
    assert (&b==&d);

    /* b+0 return a right value */
    decltype(b+0) e = b;
    assert (&b!=&e);
}

void mod_test ()
{
    assert (5/3==1);
    assert (-5/3==-1);
}

void overflow()
{
    /* overflow */
    int i = INT_MAX;
    int j = i + 1;
}

int main ()
{
    right_value();
    mod_test();
    return 0;
}
