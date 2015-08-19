#include <zmq.h>
#include <stdio.h>
#include <assert.h>

int main ()
{
    void*context = zmq_ctx_new ();
    assert (context);

    /* any number to be int */
    int cc = zmq_ctx_set (context, ZMQ_IO_THREADS, 88888888);
    if (cc) {
        fprintf (stderr, "%d: %s", zmq_errno(), zmq_strerror(zmq_errno()));
        zmq_ctx_destroy (context);
        return -1;
    }

    zmq_ctx_destroy (context);
    return 0;
}
