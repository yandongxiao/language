#include <iostream>

using namespace std;

int main ()
{
    int nums[] = {1,2,4};

    /* int [3] */
    decltype(nums) rr1 = {1,2,3};

    /* int (&)[3] */
    decltype((nums)) rr2 = rr1;
	
    cout << rr2[0] <<endl;

    return 0;
}
