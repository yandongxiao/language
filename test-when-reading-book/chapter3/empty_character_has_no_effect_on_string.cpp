#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
    /* if we append '\0' */
    string s = "123";
    s += '\0';
    s += "456";

    cout << s << endl;

    return 0;
}
