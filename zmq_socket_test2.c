#include <zmq.h>
#include <stdio.h>
#include <pthread.h>
#include <czmq.h>

/* server read data in round-robin, no delimeter or ID */

void*
client_thread (void *arg)
{
    int cc;
    int idx = (int)arg;

    char msg[128];
    sprintf(msg, "%d client", idx);

    void *ctx = zmq_ctx_new ();
    assert (ctx);

    void *serv = zmq_socket (ctx, ZMQ_REQ);
    assert (serv);

    /**/
    zmq_setsockopt (serv, ZMQ_IDENTITY, msg, strlen(msg));

    cc = zmq_connect (serv, "tcp://localhost:5555");
    assert (cc==0);

    while (1) {
        zmq_send (serv, msg, strlen(msg), 0);

        char buff[128];
        int len = zmq_recv (serv, buff, 128, 0);
        buff[len]=0;
        printf ("client%d : read <%s>\n" , idx, buff);

    }

}

int main ()
{
    int cc;
    
    int i;
    for (i=0; i<2; i++) {
        zthread_new (client_thread, (void*)i);
    }

    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *serv = zmq_socket (ctx, ZMQ_REP);
    assert (serv);

    zmq_setsockopt (serv, ZMQ_IDENTITY, "server", strlen("server"));

    cc = zmq_bind (serv, "tcp://*:5555");
    assert (cc==0);

    while (1) {
        sleep (1);

        char buff[128];
        int len = zmq_recv (serv, buff, 128, 0);
        buff[len]=0;
        printf ("server : read <%s>\n", buff);
        
        zmq_send (serv, "hello, I am server", strlen("hello, I am server"), 0);
    }
    
    return 0;
}
