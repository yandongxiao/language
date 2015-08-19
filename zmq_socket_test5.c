#include <czmq.h>
#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include "zhelpers.h"

void*
do_proxy (void *arg)
{
    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *front = zmq_socket (ctx, ZMQ_ROUTER);
    zmq_bind (front, "tcp://*:5555");

    void *end = zmq_socket (ctx, ZMQ_DEALER);
    zmq_bind (end, "tcp://*:6666");

    while (1) {
        char *id = s_recv (front);
        assert (strcmp(id, "client")==0);
        char *delimiter = s_recv (front);
        assert (strcmp(delimiter, "")==0);
        char *contents = s_recv (front);
        s_sendmore (end, id);
        s_sendmore (end, delimiter);
        s_send (end, contents);
        
        printf ("get message from client: <%s>\n", contents);

        id = s_recv (end);
        assert (strcmp(id, "client")==0);
        delimiter = s_recv (end);
        assert (strcmp(delimiter, "")==0);
        contents = s_recv (end);
        s_sendmore (front, id);
        s_sendmore (front, delimiter);
        s_send (front, contents);
        
        printf ("get message from server: <%s>\n", contents);

    }
}

void *
do_reply (void *arg)
{
    void *ctx = zmq_ctx_new ();
    assert (ctx);

    void *worker = zmq_socket (ctx, ZMQ_REP);
    zmq_connect(worker, "tcp://localhost:6666");

    while (1) {
        char *contents = s_recv (worker);
        printf ("worker: recv message <%s>\n", contents);
        s_send (worker,"I am worker");
    }

    return NULL;
}

int main ()
{
    zthread_new (do_proxy, NULL);
    zthread_new (do_reply, NULL);

    void *ctx = zmq_ctx_new ();
    assert (ctx);
    void *client = zmq_socket (ctx, ZMQ_REQ);
    zmq_setsockopt (client, ZMQ_IDENTITY, "client", 6);
    zmq_connect(client, "tcp://localhost:5555");
    
    while (1) {
        sleep (1);
        s_send (client, "i am client");
        char *msg = s_recv (client);
        printf ("client: recv message <%s>\n", msg);

    }

    return 0;
}
