#include <iostream>

using namespace std;

int main ()
{
    int val;
    int sum = 0;
    while (cin >> val) {
        /**
         * 1. try to input double type, cin will be invalid.
         * "." is not recoganized
         */
        sum += val;
    }

    cout << "sum is <" << sum << ">" << endl;

    return 0;
}
