#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

void test ()
{
    throw range_error("no such value");
}

int main ()
{
    try {
        test();
    } catch (range_error err) {
        cout << "range_error()" <<endl;
        cout << err.what() <<endl;
    } catch (runtime_error err) {
        cout << err.what() <<endl;
    }

    return 0;
}
