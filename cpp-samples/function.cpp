#include <stdio.h>
#include "function.h"

class CPP {
    int num;
public:
    void method();
};

EXTERNC void
method(CPP *c)     /* note: the parameter */
{
    printf ("method called\n");
    return;
}

EXTERNC void test ()
{
//    std::cout << "test called" << std::endl;  /* will happend link error */
    int a = 0;
    auto b = a;
    printf ("test called, hello world\n");
}
