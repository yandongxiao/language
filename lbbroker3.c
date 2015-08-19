#include <stdio.h>
#include <unistd.h>
#include <czmq.h>
#include <string.h>

#define NBR_CLIENTS 1
#define NBR_WORKERS 1

static void*
client_task(void *arg)
{
    zctx_t *ctx = zctx_new ();
    zsocket_t *client = zsocket_new (ctx, ZMQ_REQ);
    zsocket_connect (client, "tcp://localhost:5555");
    
    while (1) {
        char buff[128];
        sprintf (buff, "hi, i am client <%s>", arg);
        zframe_t *frame = zframe_new (buff, strlen(buff)+1);
        zframe_send (&frame, client, 0);
        char *reply = zstr_recv (client);
        printf ("%s: get reply <%s>\n\n\n", arg, reply);
        free (reply);
        
        sleep (1);
    }
}

static void*
worker_task(void *arg)
{
    zctx_t *ctx = zctx_new ();
    zsocket_t *worker = zsocket_new (ctx, ZMQ_REQ);
    zsocket_connect (worker, "tcp://localhost:6666");

    zstr_send (worker, "ready");

    while (1) {
        zmsg_t *msg = zmsg_recv (worker);
        if (!msg)
            break;
        
        printf ("%s: get request <%s>\n", arg, zframe_data(zmsg_last(msg)));
        
        char buff[128];
        sprintf (buff, "hi, i am worker <%s>", arg);
        zframe_reset (zmsg_last(msg), buff, strlen(buff)+1);

        zmsg_send (&msg, worker);
    }
}

typedef struct {
    zsocket_t *front;
    zsocket_t *end;
    zlist_t *worker;
} broker_t;

int
s_handle_front (zloop_t *loop, zmq_pollitem_t *poller, void *arg)
{
    broker_t *broker = (broker_t *) arg;

    zmsg_t *msg = zmsg_recv (broker->front);
    if (!msg)
        return 0;
    
    zmsg_wrap (msg, (zframe_t *)zlist_pop(broker->worker));
    zmsg_send (&msg, broker->end);
    
    if (zlist_size(broker->worker)==0) {
        zmq_pollitem_t poller = {broker->front, 0, ZMQ_POLLIN};
        zloop_poller_end (loop, &poller);
    }
}

int
s_handle_back (zloop_t *loop, zmq_pollitem_t *poller, void *arg)
{
    broker_t *broker = (broker_t *) arg;

    zmsg_t *msg = zmsg_recv (broker->end);
    if (!msg)
        return 0;
    
    zframe_t *worker_frame = zmsg_unwrap (msg);
    zlist_append (broker->worker, worker_frame);

    if (zlist_size(broker->worker)==1) {
        zmq_pollitem_t poller = {broker->front, 0, ZMQ_POLLIN};
        zloop_poller(loop, &poller, s_handle_front, broker);
    }

    zframe_t *frame = zmsg_first(msg);
    if (strcmp(zframe_data(frame), "ready") != 0) {
        zmsg_send (&msg, broker->front);
    } else {
        zmsg_destroy(&msg);
    }
}

int main ()
{
    zctx_t *ctx = zctx_new ();
    zsocket_t *frontend = zsocket_new (ctx, ZMQ_ROUTER);
    zsocket_t *backend = zsocket_new (ctx, ZMQ_ROUTER);
    zmq_bind (frontend, "tcp://*:5555");
    zmq_bind (backend,  "tcp://*:6666");

    int client_nbr; 
    for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++) {                                
        char *buff = malloc (128);
        sprintf(buff, "client%d", client_nbr);
        zthread_new (client_task, buff);                 
    }
    
    int worker_nbr; 
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++) {                                
        char *buff = malloc (128);
        sprintf(buff, "worker%d", worker_nbr);
        zthread_new (worker_task, buff);                 
    }

    broker_t *broker =  zmalloc (sizeof(broker_t));
    broker->front = frontend;
    broker->end = backend;
    broker->worker = zlist_new();

    zloop_t *reactor = zloop_new ();
    zmq_pollitem_t poller = {broker->end, 0, ZMQ_POLLIN};
    zloop_poller(reactor, &poller, s_handle_back, broker);
    zloop_start (reactor);
    zloop_destroy(&reactor);

    return 0;
}
