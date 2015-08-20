#include <iostream>

using namespace std;

int
main ()
{
    int val = 0;
    int sum = 0;

    while (cin>>val)
        sum += val;
    cin.clear();

    /* input: 1 2 3 d. output: 6 */
    /* input: 1 2 3d.  output: 6 */
    cout << "sum = " << sum <<endl;

    return 0;
}
