#include <zmq.h>
#include <stdio.h>
#include <pthread.h>
#include <czmq.h>
#include <assert.h>


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
        if (len==0) {
            len = zmq_recv (serv, buff, 128, 0);
            assert (len != 0);
        }
        buff[len]=0;

        printf ("%s : read <%s>\n", endpont, buff);
        /* send two frame to client: delimeter and contents */
        zmq_send (serv, endpont, strlen(endpont), 0);

        int cc = zmq_send (serv, endpont, strlen(endpont), 0);
        if (cc==-1) {
            fprintf(stderr, "you can not allowed to do\n");
        }
    }

}


int main ()
{
    int cc;
    
    zthread_new (server_thread, "tcp://*:6666");
    zthread_new (server_thread, "tcp://*:5555");

    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *client = zmq_socket (ctx, ZMQ_DEALER);
    assert (client);

    cc = zmq_connect (client, "tcp://localhost:5555");
    assert (cc==0);
    cc = zmq_connect (client, "tcp://localhost:6666");
    assert (cc==0);

    while (1) {
        sleep (1);
        zmq_send (client, "", 0, ZMQ_SNDMORE);
        zmq_send (client, "hello, I am client1", strlen("hello, I am client1"), 0);

        zmq_send (client, "", 0, ZMQ_SNDMORE);
        zmq_send (client, "hello, I am client2", strlen("hello, I am client2"), 0);
        
        char buff[128];
        int len = zmq_recv (client, buff, 128, 0);
        if (len==0) {
            len = zmq_recv (client, buff, 128, 0);
            assert (len!=0);
        }
        buff[len]=0;
        printf ("client : read <%s>\n", buff);
    }
    
    return 0;
}
