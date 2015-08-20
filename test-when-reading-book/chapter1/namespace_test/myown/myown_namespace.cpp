#include <iostream>

/* 1. the definition like iostream */
#include "myown_namespace1.h"
#include "myown_namespace2.h"

/* using usage */
using dxyan::val1;
using dxyan::int_one;

int main ()
{
    dxyan::int_one val = 10;
    dxyan::val2 = 200;    

    std::cout << val << std::endl;
    std::cout << dxyan::val2 << std::endl;

    return 0;
}
