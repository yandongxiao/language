#include <stdio.h>
#include <unistd.h>

#ifndef HOSTNMAE_MAX
#define HOSTNAME_MAX    512
#endif

int
main (void)
{
    char buffer [HOSTNAME_MAX];
    gethostname (buffer, HOSTNAME_MAX);

    printf ("%s\n", buffer);
    return 0;
}
