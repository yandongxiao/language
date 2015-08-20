#include <iostream>
#include "class_static_member.h"
using namespace std;

/* you should better define the static const valriable */
int example::count = 10;
const int example::val2 = 20;
constexpr int example::val3;

int example::get_count ()
{
    return count;
}

void test (const int &num = example::val3)
{
    cout << "test" << endl;
}

int main ()
{

    cout << example::get_count() << endl;

    cout << example::val2 << endl;

    cout << example::val3 << endl;

    return 0;
}
