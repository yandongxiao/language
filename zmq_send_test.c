#include <zmq.h>
#include <stdio.h>
#include <assert.h>

/* client can be started before server. */
int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    void *socket = zmq_socket (contex, ZMQ_REQ);
    int cc = zmq_connect (socket, "tcp://redhat-64:5555");
    assert (cc==0);
    printf ("connect on 5555 successfully\n");
  
    while (1) {
        cc = zmq_send (socket, "hello", 5, 0);
        assert (cc==5);
        
        char buff[128];
        zmq_recv (socket, buff, 128, 0);

    }
   
    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
