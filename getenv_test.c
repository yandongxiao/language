#include <stdio.h>
#include <stdlib.h>

int 
main (void)
{
    char *value = getenv ("PATH");
    printf ("PATH=%s\n", value);
    return 0;
}
