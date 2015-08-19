#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);
    
    void *socket = zmq_socket (contex, ZMQ_SUB);
    assert (socket);
    int cc = zmq_connect (socket, "tcp://localhost:5555");
    assert (cc==0);

    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);
    while (1) {
        char buff[256];
        int cc = zmq_recv (socket, buff, 256, 0);
        assert (cc>0);
        buff[cc] = 0;
        printf ("%s\n", buff);
    }

    return 0;
}
