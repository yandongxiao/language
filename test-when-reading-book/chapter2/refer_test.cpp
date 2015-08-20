#include <iostream>
#include <cassert>
using namespace std;

int main ()
{

    /* 1. you can use & on refer */
    int i = 0;
    int &ri = i;
    assert (&i==&ri);

    /* they musch strict match */
    //const int ci = 1;
    //int &rci = ci;

    /* except one */
    const int &rci = i;
}
