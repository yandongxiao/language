#include <iostream>
#include <bitset>

int main ()
{
    char a = 0222;
    a = a << 8;

    std::cout << (int)a << std::endl;
    return 0;
}
