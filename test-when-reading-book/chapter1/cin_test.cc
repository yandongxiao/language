#include <iostream>
#include <climits>
using namespace std;


int main ()
{
    int val;

    /**
     * operator return the reference of cin
     * see object_as_condition for more information abut cin >> val
     * every time we get an input, check the status of cin
     * cin will return when read a while space or new line
     */
    while (cin >> val)
        cout << val << endl;

    /**
     * If cin fails, there are two kind of error.
     * recoverable error, e.g. read EOF, you can invoke cin.clear() to make cin to good
     * fatal error. there is no way to recover.
     */
    if (cin.eof()) {
        cout << "end of file" << endl;
        cin.clear();    /* return void */
        if (cin >> val)
            cout << "cin can read data like before" << endl;
        return 0;
    }

    cout << val << "is not an integer" << endl;
    if (cin.bad()) {
        cout << "unrecoverable error" << endl;
        return -1;
    } else {
        cout << "recoverable error" << endl;
        cin.clear();
    }

    /**
     * you must clean the input buffer, or next time cin will return the same error
     */
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  /* ignore the char until '\n' */

    /**
     * only cin is valid, val is valid
     */
    if (cin >> val)
        cout << "the last val is : " << val << endl;
    return 0;
}
