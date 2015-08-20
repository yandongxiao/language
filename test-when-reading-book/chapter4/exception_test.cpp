#include <iostream>
#include <stdexcept>    /*for runtime_error*/

using namespace std;

void throw_test ()
{
    /* throw a object */
    throw runtime_error ("run time error");
}

int main ()
{
    try {
        throw_test();
        cout << "after" << endl;
    } catch (exception err) {
        cout << "exception : " << err.what() << endl;
    } catch (runtime_error err) {
        /*it will not be called*/
        cout << "runtime_error : "<< err.what() << endl;
    }

    cout << "end" <<endl;

    return 0;
}
