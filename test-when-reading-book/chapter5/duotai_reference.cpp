#include <iostream>

using namespace std;

class BASE {
public:
    virtual void vfunc (void) {cout << "base" <<endl;}
};

class DERIVED : public BASE {
public:
    virtual void vfunc(void) {cout << "derived" <<endl; }
};

/* test BASE *base, BASE &base, BASE base */
void test (BASE base) {
    base.vfunc();
}

int main ()
{
    DERIVED d;    
    test(d);

    /* yes */
    BASE base;
//    DERIVED dd=base;
    return 0;
}
