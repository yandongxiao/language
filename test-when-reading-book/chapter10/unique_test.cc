#include <algorithm>
#include <iostream>
using namespace std;

int main ()
{
    vector<int> vec = {1,2,3,4,3};
    auto iter_end = unique (vec.begin(), vec.end());
    for (auto iter=vec.begin(); iter != iter_end; iter++) {
        cout << *iter << endl;
    }

    return 0;
}
