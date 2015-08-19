#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* client can be started before server. */
int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    /* I am server */
    void *socket = zmq_socket (contex, ZMQ_REQ);
    int cc = zmq_bind (socket, "tcp://eth0:5555");
    assert (cc==0);
    printf ("connect on 5555 successfully\n");
  
    cc = zmq_send (socket, "hello, sss", strlen("hello, "), ZMQ_SNDMORE);
    cc = zmq_send (socket, "It is a bad day", strlen("It is a bad day"), 0);
    
    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
