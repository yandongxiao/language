#include <string>
#include <iostream>

using std::string;
using std::cout; using std::endl;

class TTT {
public:
    TTT (const TTT &t):a(t.a) { cout<<"TTT (const TTT &t)" << endl;}
    TTT (const TTT &&t):a(t.a) { cout<<"TTT (const TTT &&t)" << endl;}
    TTT (int i=0): a(i){cout<<"TTT (int i=" << i << ")"<<endl;}
private:
    int a = 10;
};

void
list_initialize ()
{
    TTT t{10}; /* OK */

    /* smart CPP */
    TTT ts[10] = {1,2,3,5}; /* copy direct */

    /* smart CPP */
//    int num{2.3};
    double dd{2};
}

int main ()
{
    /* string(const char *) construct and copy/move construct?
     * yes, but compiler optmize will make program do not call copy/move construct */
    string str = "123";

    TTT t2 = 10;    /* copy initialze */
    TTT t3(10);     /* direct initialze */

//    list_initialize ();

    return 0;
}
