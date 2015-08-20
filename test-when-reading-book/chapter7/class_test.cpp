#include <vector>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class QQQ;

class TTT
{
public:
    /* error : use size_type after typedef */
//    size_type getval(){}
    typedef string::size_type size_type;
    using size_tt = size_type;    /* C++ 11 way */
    size_type getnum();
    TTT(int){}
    /* you can declare, but not define */
    void func(QQQ q);
};

/*
 * 1. just declrate inline here
 * 2. it should be in header file
 */
inline TTT::size_type
TTT::getnum ()
{
    return 0;
}

int g_int;

class QQQ
{
    mutable int num;    /* event const var can change this filed */
    TTT t = TTT(2);     /* special ha */
public:
    void getcalled() const {num++;}
    void getcalled() {num++;}

    /* like function's default value */
    int b = g_int;
};

void TTT::func(QQQ q){}

int main ()
{
    TTT::size_type t = 10;

    QQQ q;
    q.getcalled();
    
    const QQQ cq = QQQ();
    cq.getcalled();
    assert (cq.b==0);
    
    g_int=100;
    QQQ dd;
    assert (dd.b == 100);
    
    return 0;
}
