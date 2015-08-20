#include <vector>
#include <iostream>

using namespace std;

/* set default value */
int func (int a1, int a2, int a3);
int func (int a1, int a2, int=3);
//int func (int a1, int a2, 3); /* error */
int func (int a1, int=2, int);
int func (int=1, int, int);

int func (int a1, int a2, int a3)
{

}

int gi = 10;
void test(int a, int b=gi);

void test(int a, int b)
{
    cout << b << endl;
}

int main ()
{
    /* It is OK */
    int a;
    func (10);


    /* print different value */
    test (1);
    gi = 100;
    test (1);

    return 0;
}
