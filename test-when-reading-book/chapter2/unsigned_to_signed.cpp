#include <iostream>

using namespace std;

int main ()
{
    long long i = 0x0FFFFFFFFFFF;
    unsigned j = 10;

    /* there is not a warnning */
    int val = i+j;
    cout << sizeof(i+j) <<endl;     /* 64 */
    cout << val <<endl;

    return 0;
}
