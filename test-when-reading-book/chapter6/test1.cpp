#include <vector>
#include <iostream>

using namespace std;

void func (int a)
{
    cout << "func(int a)" <<endl;
}

void func (int &a)
{
    cout << "func(int &a)" <<endl;
}

int main ()
{
    int num = 10;

    /* ambiguous, but they two functions are legal */
//    func (num);

    /* OK */
    func(num+0);

    /* ambiguous */
    int *p = &num;
//    func(*p);

    
    /* If I pass a left value, ambiguous */
    /* If I pass a right value, ok */

    return 0;
}
