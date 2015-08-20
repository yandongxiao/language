#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class PPP
{
    PPP(){}
public:
    PPP(int num){}
};


class TTT
{
    int num;
    /* you can not set it as member */
   PPP p;
public:
    /* no const TTT */
    /* handle no PPP(), like this*/
    TTT(int num): p(0){}
    TTT(double num): p(0){}
    TTT(const TTT &): p(0){}
    TTT(TTT &): p(0){}
    TTT() : p(0){}

    // TTT(TTT &) const {}  /* no such */
};


class QQQ
{
public:
    int a = 0;  /* c++ 11 support */
    int b = 0;
    /* the order of expression executed */
    QQQ(int num) : b(num++), a(num++) {}
    QQQ() = default;
};

int main ()
{
    /* PPP() is private */
    //PPP p;
    //TTT t;


    QQQ q(10);
    assert (q.a == 10);
    assert (q.b == 11);

    /* the value initialized to 0 */
    vector<QQQ> vecq(1);
    assert (vecq[0].a == 0);
    assert (vecq[0].b == 0);

    return 0;
}
