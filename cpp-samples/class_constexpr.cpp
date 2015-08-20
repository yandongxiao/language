#include <iostream>
using namespace std;

struct example {
    int val1;
    int val2;
    int getval () {return val1+=1;}
};

constexpr struct example test ()
{
    return {1,1};
}

int main ()
{
    constexpr struct example v = {1,1};
}
