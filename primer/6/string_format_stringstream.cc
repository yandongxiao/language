#include <sstream>
#include <iostream>
using namespace std;

int main ()
{
    /* istringstream and ostringstream */
    stringstream s;
    s<<"line:"<<10;
    string str = s.str();

    cout << str <<endl;

    return 0;
}
