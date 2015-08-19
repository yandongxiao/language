#include <stdio.h>
#include <string.h>


int
main (void)
{
    char * p = strstr ("helloworld", "w");
    printf ("%s\n", p);
    return 0;
}
