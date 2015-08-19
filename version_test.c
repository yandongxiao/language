#include <zmq.h>
#include <stdio.h>

int main ()
{
    int major;
    int minor;
    int patch;

    zmq_version (&major, &minor, &patch);

    printf ("ZMQ version : %d.%d.%d\n", major, minor, patch);

    return 0;
}
