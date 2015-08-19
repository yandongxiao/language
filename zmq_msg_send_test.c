#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    void *socket = zmq_socket (contex, ZMQ_REQ);
    int cc = zmq_bind (socket, "tcp://eth0:5555");
    assert (cc==0);
    printf ("connect on 5555 successfully\n");

    /* send a meesage, do not consider the network order */
    zmq_msg_t msg;
    zmq_msg_init_size (&msg, sizeof(10));
    void *data = zmq_msg_data(&msg);
    *(int*)data = 10;
    zmq_msg_send (&msg, socket, 0);
    zmq_msg_close (&msg);

    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
