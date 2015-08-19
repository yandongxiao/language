#include <sys/socket.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    printf("%d\n",FD_SETSIZE);
    return 0;
}
