#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class TTT
{
public:
    /* call you */
    TTT(string s){cout <<"TTT(string s)"<<endl;}
};

void
test_cast_create_object (TTT t)
{
    /* yesy */
}

int main ()
{
    string s = "123";
    test_cast_create_object(s);
    return 0;
}
