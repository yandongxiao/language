#include <iostream>

using namespace std;

int main ()
{
    int i = -74;
    unsigned j = 28;

    /* 1. convert i to unsigned. rule is j(mod) */
    cout << i+j <<endl;

    /* 2. val is what we want, but 
     * the value of @val is undefined. i+j out of val range.
     */
    int val = i+j;
    cout << val << endl;

    return 0;
}
