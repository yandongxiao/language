#include <cassert>
#include <string>
using namespace std;

/**
 * how to make an object as a condition in if,while,for.
 * Note: it is not C++11 feasure
 */

class Phone {
public:
    string version;
    /* can be 0 for developers */
    double price;

    /**
     * type conversion operator
     * Note: no return value, no parameters, do not change members
     */
    operator bool() const;
};

Phone::operator bool() const
{
    if (price > 0)
        return true;
    return false;
}

int main ()
{
    Phone p1;
    p1.price = 0;
    assert (p1 == false);

    Phone p2;
    p2.price = 20;
    assert (p2 == true);

    return true;
}