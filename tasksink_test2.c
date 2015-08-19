#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main ()
{
    void *contex = zmq_ctx_new();
    assert (contex);
    
    void *socket = zmq_socket (contex, ZMQ_PULL);
    assert (socket);
    int cc = zmq_bind (socket, "tcp://*:6666");
    assert (cc==0);
    
    void *control = zmq_socket(contex, ZMQ_PUB);
    assert (control);
    zmq_bind (control, "tcp://*:7777");
    assert (cc==0);

    char buff[128];
    cc = zmq_recv (socket, buff, 128, 0);
    assert (cc==5);
    buff[cc] = 0;
    cc = strcmp(buff, "start");
    assert (cc==0);

    int i;
    for (i=0; i<100*1000; i++) {
        cc = zmq_recv (socket, buff, sizeof(buff), 0);
        buff[cc]=0;
        printf ("get the message : <%s>\n", buff);
    }

    printf ("all message have benn get handled\n");
    zmq_send (control, "stop", strlen("stop"), 0);

    zmq_close (control);
    zmq_close (socket);
    zmq_ctx_destroy(contex);
    return 0;
}
