#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int nums[] = { 1, 2, 3, 4, 5, 55, 5 };
    int len = sizeof(nums) / sizeof(nums[0]);

    auto cnt = count(nums, nums + len, 5);
    cout << cnt << endl;

    return 0;
}

