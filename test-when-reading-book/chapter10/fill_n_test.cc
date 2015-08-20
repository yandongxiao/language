#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
    vector<int> vec;
    vec.reserve(10);
    fill_n (vec.begin(), 10, 0);
    cout << vec.capacity() << endl;
    for (auto i : vec) {
        cout << i << endl;
    }

    return 0;
}
