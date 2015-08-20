#include <vector>
#include <iostream>

using namespace std;

class QQQ;
class TTT;

class MMM {
public:
    /* if this function use member of TTT, just declaration. */
    void mmethod(TTT &t);
};


class TTT {

/* out of contro of public and private */
friend istream& operator >> (istream &in, TTT &t);
friend void getnum(){cout<<"getnum"<<endl;}
friend class QQQ;

/* 1. mmethod must be public
 * 2. must define the MMM before
 */
friend void MMM::mmethod(TTT &t);
private:
    int a;
};

/* in header file, declaration is necessary */
istream& operator >> (istream &in, TTT &t);

/* must : declaration like this */
void getnum();

istream& operator >> (istream &in, TTT &t)
{
    in >> t.a;
    return in;
}

void MMM::mmethod(TTT &t)
{
    cout << t.a << endl;
}

class QQQ {
    int a;
public:
    
    QQQ(TTT &t){this->a=t.a;}
};

int main ()
{
    TTT t;
    cin >> t;

    getnum();   /* OK */
    //TTT::getnum();    /* error, TTT:: not should be used to freind */
    
    /* friend class */
    QQQ q(t);


    MMM m;
    return 0;
}
