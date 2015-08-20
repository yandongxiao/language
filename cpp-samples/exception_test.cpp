#include <iostream>
#include <stdexcept>

/* http://blog.csdn.net/crazyhacking/article/details/9713987 */

using namespace std;

int main ()
{
    int val = 0x7FFFFFFF;

    try {    
        val *= 0x7FFFFFFFFFFFFFFF;
        cout << val << endl;
    }
    catch (overflow_error except) {
        cerr << except.what() << endl;
    }

    return 0;
}
