#include <vector>
#include <iostream>

using namespace std;

class TTT {
private:
    int b;
public:
    int a;
};

int main ()
{
    /* a must be public priority */
    cout << sizeof(TTT::a) << endl;
//    cout << sizeof(TTT::b) << endl;   /* NO */
    cout << sizeof(TTT) << endl;
    return 0;
}
