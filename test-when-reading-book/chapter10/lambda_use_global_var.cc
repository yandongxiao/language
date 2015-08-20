#include <algorithm>
#include <iostream>

using namespace std;

int global;	/* can not be included in lambda */

int main ()
{
    int nums[] = {1,2,3,4,5};
    int local;

    sort(nums, nums+5, [local](int a, int b){return a>b;});

    for (int v: nums)
        cout << v << endl;


    return 0;
}

