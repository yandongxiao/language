#include <iostream>
using namespace std;

void func () { cout << "func" <<endl;}

/* totally same with array */
decltype((func)) factory(int num)
{
    decltype(func) *p = func;
    return *p;
}

int main ()
{
    decltype(func) ttt;
    /* no such way */
//    ttt =  factory(0);
    decltype((func)) rrr = factory(0);
    rrr();


    decltype(func) *ppp = factory(0);
    ppp();

    return 0;
}
