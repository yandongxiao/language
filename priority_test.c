#include <stdio.h>

int main ()
{
    int buf[2] = {0,0};
    int *p = buf;

    printf ("val is %d\n", *p++);

    return 0;
}
