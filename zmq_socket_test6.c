#include <zmq.h>
#include <stdio.h>
#include <pthread.h>
#include <czmq.h>
#include <assert.h>
#include "zhelpers.h"

void*
server_thread (void *arg)
{
    int cc;

    char *endpont = strdup(arg);
    assert (endpont);

    void *ctx = zmq_ctx_new ();
    assert (ctx);

    void *serv = zmq_socket (ctx, ZMQ_ROUTER);
    assert (serv);
    cc = zmq_connect (serv, endpont);
    assert (cc==0);

    while (1) {
        char *id = s_recv (serv);
        printf ("%s : identity <%s>\n", endpont, id);
        char *content = s_recv (serv);
        printf ("%s : read <%s>\n", endpont, content);
        /* send two frame to client: delimeter and contents */
        s_sendmore (serv, id);
        s_send (serv, content);
    }

}


int main ()
{
    int cc;
    
    zthread_new (server_thread, "tcp://localhost:5555");

    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *client = zmq_socket (ctx, ZMQ_DEALER);
    assert (client);

    /* it is necessary for ZMQ_DEALER<-->ZMQ_ROUTER */
    zmq_setsockopt (client, ZMQ_IDENTITY, "client", 6);
    
    cc = zmq_bind (client, "tcp://*:5555");
    assert (cc==0);

    while (1) {
        sleep (1);
        zmq_send (client, "hello, I am client1", strlen("hello, I am client1"), 0);
        char buff[128];
        int len = zmq_recv (client, buff, 128, 0);
        buff[len]=0;
        printf ("client : read <%s>\n", buff);
    }
    
    return 0;
}
