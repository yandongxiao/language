#include <iostream>
#include <vector>
using namespace std;

class ttt {
    int a = 10;
public:
    ttt (ttt &a) { cout << "copy constructor" <<endl; }
    ttt () = default;
    ttt (int a) {return;};
    ttt& operator = (ttt &a) {cout << "assign operator"<<endl;}
};

ttt test (ttt t) {
    return t;
}

ttt t;

void test()
{
    /* copy constructor */
    test (t);

    ttt t2;
    t2 = t;
}

int main ()
{


    return 0;
}
