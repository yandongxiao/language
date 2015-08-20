#include <vector>
#include <iostream>
#include <iterator> /* for begin and end */
using namespace std;

int main ()
{
    /* element is not initialized */
    int num [10];

    /* compile error */
    //int num2 [3] = {1,2,3,4};
    //char buff [5] = "hello";

    decltype(num) v1 = {1,2,3,4};
    decltype((num)) v2 = v1;    /* int (&)[10] */

    int *p = begin(num);
    int *e = end (num);
    cout << "len is : " << e-p <<endl;

    /* can be negtive value */
    p = &num[2];
    p[-2];      /* equal num[0] */
    return 0;
}
