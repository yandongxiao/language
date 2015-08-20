#include <vector>
#include <iostream>

using namespace std;

class TTT {
    int num;
public:
    int getnum() const;
    int setnum();
    int setnum() const; /* overload */
//    TTT() = default;
};

int TTT::getnum() const
{
//    int this;  /* error */

    /* define a num with same name */
    int num = 0;

    const TTT *const p = this;
    const TTT *q = this;

//  TTT *s = this;  /* error */

    return num;
}

int TTT::setnum() 
{
    cout << "TTT::setnum() " << endl;
    this->num = 0;
}

int TTT::setnum() const
{
    cout << "TTT::setnum() const" <<endl;
    return 0;
}

int main ()
{
    TTT t1;
    /* 1. init like this, or uninit error */
    const TTT t2 = t1;

    /* 2. init like this, or uninit error */
    const TTT t3 = TTT();

    /* t2,t3 can not invoke it. even setnum nothing to do*/
    t1.setnum();

    /* t1 can invoke it*/
    t1.getnum();


    t1.setnum();
    t2.setnum();

    return 0;
}
