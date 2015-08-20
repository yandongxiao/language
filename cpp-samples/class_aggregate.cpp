#include <iostream>
#include <string>

using namespace std;

struct example 
{
    string name;
    int age;
    bool male;
    int children;
};

int main ()
{
    struct example p = {"dxyan", 10};

    cout << p.male << endl;

    cout << p.children << endl;

    return 0;
}
