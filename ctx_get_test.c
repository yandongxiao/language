#include <zmq.h>
#include <assert.h>
#include <stdio.h>

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    int val = zmq_ctx_get (contex, ZMQ_IO_THREADS);
    printf ("default value of ZMQ_IO_THREADS is : %d\n", val);

    val = zmq_ctx_get (contex, ZMQ_MAX_SOCKETS);
    printf ("default value of ZMQ_MAX_SOCKETS is : %d\n", val);

    return 0;

}

