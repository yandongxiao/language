#include <vector>
#include <iostream>

using namespace std;

int func (int *p){cout<< "func(int *p)" <<endl;}

int func (const int *q){cout << "func(const int *q)" << endl;}

int main ()
{
    /* It is OK */
    int a;
    func (&a);


    return 0;
}
