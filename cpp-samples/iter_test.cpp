#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;


void iter_test ()
{
    vector<int> nums = {1,2,3,4,5,6};
    auto begin = nums.begin();
    auto end = nums.end();
    cout << end - begin <<endl;
}

void pointer_test ()
{
    int nums [] = {1,2,3,4,5,6};    /* int [] nums is error. */
    int *begin = &nums[0];
    int *end = &nums[6];

    cout << end - begin <<endl;
}


int main ()
{
    iter_test ();
    pointer_test ();

}
