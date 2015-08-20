#include <iostream>

using namespace std;

void test()
{
    cout << "test()" << endl;
}


class example {

public:
    void test (){ cout << "example::test()" << endl; }
    void use_test (){ ::test(); }
};

int main ()
{
    example e;
    e.use_test ();

    return 0;
}
