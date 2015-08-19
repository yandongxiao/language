#include <zmq.h>
#include <stdio.h>
#include <pthread.h>
#include <czmq.h>

/* test for:
 *    1. client will use round-robin manner to send request to all its client.
 *    2. the message has only one frame, no matter zmq_setsockopt called or not.
 */ 

void*
server_thread (void *arg)
{
    int cc;

    char *endpont = strdup(arg);
    assert (endpont);

    void *ctx = zmq_ctx_new ();
    assert (ctx);

    void *serv = zmq_socket (ctx, ZMQ_REP);
    assert (serv);
    cc = zmq_bind (serv, endpont);
    assert (cc==0);

    while (1) {
        char buff[128];
        int len = zmq_recv (serv, buff, 128, 0);
        buff[len]=0;
        printf ("%s : read <%s>\n", endpont, buff);

        zmq_send (serv, endpont, strlen(endpont), 0);
    }

}


int main ()
{
    int cc;
    
    zthread_new (server_thread, "tcp://*:6666");
    zthread_new (server_thread, "tcp://*:5555");

    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *client = zmq_socket (ctx, ZMQ_REQ);
    assert (client);

    /* It has no effect */
    zmq_setsockopt (client, ZMQ_IDENTITY, "client", 5);

    cc = zmq_connect (client, "tcp://localhost:5555");
    assert (cc==0);
    cc = zmq_connect (client, "tcp://localhost:6666");
    assert (cc==0);

    while (1) {
        sleep (1);
        zmq_send (client, "hello, I am client", strlen("hello, I am client"), 0);
        
        char buff[128];
        int len = zmq_recv (client, buff, 128, 0);
        buff[len]=0;
        printf ("client : read <%s>\n", buff);
    }
    
    return 0;
}
