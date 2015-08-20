#include <iostream>
#include <initializer_list>

using namespace std;

initializer_list<int> func()
{
    return {1,2,3};
}

int main ()
{
    initializer_list<int> ints = func();
    for (auto &v : ints) {
        cout << v <<endl;
    }
}
