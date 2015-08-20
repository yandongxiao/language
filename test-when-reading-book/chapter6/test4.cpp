#include <vector>
#include <iostream>

using namespace std;

auto add(int a, int b) -> int
{
    return a+b;
}

void test()
{
    int nums[] = {1,2,3};

    int (*p)[3] = &nums;
    decltype(nums)* q = p;
}

int main ()
{
    cout << add (1,2) << endl;
    return 0;
}
