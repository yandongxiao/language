#include <iostream>
using namespace std;

class TTT {
    int a;
    int b;
};

void cast_test()
{
    double d = 3.14;
    int a = d + 1;

    void *pv = &a;
    char *pc = static_cast<char*>(pv);
    /*It seems that, static_cast used to remove warnning */
//    long *pl = static_cast<long*>(pc);    /* cast error*/
    long *pl = reinterpret_cast<long*>(pc);
    *pl = 10;

    
    /* first, we need a TTT(int) constructor no matter 
     * use static_cast or reinterpret_cast
     */
    int val = 10;
    //TTT t = static_cast<TTT>(val);
    //TTT t = reinterpret_cast<TTT>(val);
}

int main ()
{
    cast_test();   
}
