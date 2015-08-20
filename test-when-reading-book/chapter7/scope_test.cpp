#include <vector>
#include <iostream>

using namespace std;

class TTT {
private:
    typedef int int32;
public:
    int32 func1(int32 i);
};

/* you can use int32 here like this */
TTT::int32 TTT::func1(int32 i){}

//TTT::int32 test(){}  /* error */

class QQQ {
public:
    /* test can see @a, just for function body  */
    void test() {cout << a << endl;} 
    void test(int a){}
//    void test(int, int32){}   /* error */
    typedef int int32;
    int a;
};

int aa;
class MMM {
    int aa;
public:
    void test(){aa=::aa;}
};

int main ()
{
//    TTT::int32 val;   /* error */
    return 0;
}
