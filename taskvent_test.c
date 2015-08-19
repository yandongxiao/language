#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main ()
{
    void *contex = zmq_ctx_new();
    assert (contex);
    
    void *socket = zmq_socket (contex, ZMQ_PUSH);
    assert (socket);
    int cc = zmq_bind (socket, "tcp://*:5555");
    assert (cc==0);

    /* inform the tasksink to start to work */
    void *sink = zmq_socket (contex, ZMQ_PUSH);
    assert (sink);
    cc = zmq_connect(sink, "tcp://localhost:6666");
    assert (cc==0);
    cc = zmq_send (sink, "start", strlen("start"), 0);
    assert (cc==5); 
    /* In original socket programming, we can close the socket here. Now can we ? */
    cc = zmq_close(sink);   /* why not we use zmq_disconnect */
    assert (cc==0);

    int i;
    /* we should start workers for load balance */
    for (i=0; i<100*1000; i++) {
        char buff[10];
        sprintf(buff, "%d", i);
        /* If there is no subscriber, will it hang ?*/
        cc = zmq_send (socket, buff, strlen(buff), 0);
        assert (cc==strlen(buff));
        printf ("send the message : <%d>\n", i);
    }
    zmq_close (socket);
    zmq_ctx_destroy(contex);
    return 0;
}
