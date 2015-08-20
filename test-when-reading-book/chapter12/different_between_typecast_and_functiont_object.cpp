#include <iostream>

using namespace std;

class TTT {
public:
    int operator() (int num) {cout<<num<<endl;}
    /* get it, NO return value, the return type is int */
    operator int();
};

TTT::operator int()
{
    return 1;
}

int main ()
{
    TTT t;
    t(10);

    return 0;
}
