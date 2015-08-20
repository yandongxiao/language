#include <iostream>
using namespace std;

int gv = 10;

struct TTT {
    int *p = nullptr;
    TTT(): p(&gv) {}
    operator int*() {return p;}
};

int main ()
{
    TTT tt;
    int *p = tt;
    cout << *p << endl;
    return 0;
}
