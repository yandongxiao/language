#include <iostream>

using namespace std;

int main ()
{
    /* value initialzation */
    int val1();
    cout << val1 << endl;   /* not used, but the value is 1*/

    int val2(10);
    cout << val2 << endl;


    /* copy initialzation */
    int val3 = 3;
    cout << val3 << endl;

    /* list initialization, need c++ 11 */
    int val4 {4};
    cout << val4 << endl;

    int val5 = {5};
    cout << val5 << endl;

    /* error*/
//    val5 = {3.2};

    int a;
    cout << a <<endl;
    return 0;
}
