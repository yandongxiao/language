#include <unistd.h>
#include <fcntl.h>

int
main (void)
{
    int p[2];
    pipe2 (p, O_NONBLOCK);

    return 0;
}
