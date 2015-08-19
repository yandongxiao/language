#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

char message [1024];

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    void *socket = zmq_socket (contex, ZMQ_REP);
    int cc = zmq_connect (socket, "tcp://redhat-64:5555");
    assert (cc==0); 
    printf ("bind on server successfully\n");

    zmq_msg_t msg;
    zmq_msg_init (&msg);
    zmq_msg_recv (&msg, socket, 0);
    void *data = zmq_msg_data (&msg);
    printf ("recv the integer from server : %d\n", *(int*)data);
    zmq_msg_close(&msg);

    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
