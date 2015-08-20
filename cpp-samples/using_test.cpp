#include <iostream>

using namespace std;

int main ()
{
    using pint = int*;
    typedef int uint32_t2;  /* you can define it here. */

    int i = 0;
    pint pi = &i;
    cout << *pi << endl;

    int j;
    const pint cpi = &i;    /* const pointer. */
    cpi = &j;

}
