#include <iostream>
#include <string>
using namespace std;

class TTT {
public:
    string str;
    TTT(string str=""){}
    TTT(TTT &t){}    /* must have const */
//    TTT(TTT &&t){}    /* move constructor */
};

int main ()
{
    string str;
    TTT t = str;

}
