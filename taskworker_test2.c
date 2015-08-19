#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main ()
{
    int cc;

    void *contex = zmq_ctx_new();
    assert (contex);
    
    void *upstream = zmq_socket (contex, ZMQ_PULL);
    assert (upstream);
    cc = zmq_connect (upstream, "tcp://localhost:5555");
    assert (cc==0);

    void *downstream = zmq_socket (contex, ZMQ_PUSH);
    assert (downstream);
    cc = zmq_connect (downstream, "tcp://localhost:6666");
    assert (cc==0);

    void *control = zmq_socket (contex, ZMQ_SUB);
    assert (control);
    cc = zmq_connect (control, "tcp://localhost:7777");
    assert (cc==0);
    zmq_setsockopt(control, ZMQ_SUBSCRIBE, "", 0);

    int count=0;
    while (1) {
        zmq_pollitem_t pollitems[] = {
            {upstream, -1, ZMQ_POLLIN, 0},
            {control,  -1, ZMQ_POLLIN, 0}
        };

        zmq_poll (pollitems, 2, -1);

        if (pollitems[0].revents & ZMQ_POLLIN) {
            char buff[128];
            cc = zmq_recv (upstream, buff, sizeof(buff), 0);
            buff[cc]=0;
            usleep (100);
            printf ("handle the message <%s>\n", buff);
            zmq_send (downstream, buff, strlen(buff), 0);
        }

        if (pollitems[1].revents & ZMQ_POLLIN) {
            break;
        }
    }
    
    zmq_close(control);
    zmq_close(upstream);
    zmq_close(downstream);
    zmq_ctx_destroy(contex);
    return 0;
}
