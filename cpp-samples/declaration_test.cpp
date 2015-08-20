#include <iostream>
#include <cassert>

//int function (int i) [10];    /* error : return a array */
//int [10] function (int i);    /* error : the left side of [] is not token */

void
test ()
{
    //extern int num = 10;  /* error */
//    extern int num;
//    std::cout << num <<std::endl;
}

int main ()
{
    int a = 3;
    int b = 4;
    
    decltype (a) c = a;     /* you can use auto better. */
    decltype (a=b) d = a;

    a = 200;

    assert (a==200);
    assert (b==4);
    assert (c==3);
    assert (d==200);
}
