#include <stdio.h>

int main(void)
{
    unsigned int a = 1;
    {
        int a = 10;
    printf ("a==%d\n", a<<2);
    }
    return 0;
}
