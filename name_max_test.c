
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

/* use limit format. */

int main (void)
{
#ifdef NAME_MAX
    printf ("NAME_MAX defined to be : %d\n", NAME_MAX);
#else
    printf ("NAME_MAX not defined");
#endif

#ifdef _PC_NAME_MAX
    printf ("_PC_NAME_MAX defined to be : %ld\n", sysconf(_PC_NAME_MAX));
#else
    printf ("_PC_NAME_MAX not defined");    
#endif

    printf ("%lu\n", sysconf(_POSIX_OPEN_MAX));
}
