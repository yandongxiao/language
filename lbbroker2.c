#include <stdio.h>
#include <unistd.h>
#include <czmq.h>
#include <string.h>

#define NBR_CLIENTS 30
#define NBR_WORKERS 3

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

    int available_workers = 0;
    zlist_t *worker_queue = zlist_new();
    while (1) {
        zmq_pollitem_t items[] = {
                     { backend, 0, ZMQ_POLLIN, 0 },
                     { frontend, 0, ZMQ_POLLIN, 0 }
                     };
        
        int rc = zmq_poll (items, available_workers? 2:1, -1);
        if (rc==-1)
            break;
        
        if (items[0].revents & ZMQ_POLLIN) {
            zmsg_t *msg = zmsg_recv (backend);
            if (!msg)
                break;
            
            available_workers++;
            zframe_t *worker_frame = zmsg_pop (msg);
            zlist_append (worker_queue, worker_frame);

            zframe_t *delimiter = zmsg_pop (msg);
            zframe_destroy(&delimiter);

            zframe_t *frame = zmsg_first(msg);
            if (strcmp(zframe_data(frame), "ready") != 0) {
                zmsg_send (&msg, frontend);
            } else {
                zmsg_destroy(&msg);
            }
        }

        if (items[1].revents & ZMQ_POLLIN) {
            zmsg_t *msg = zmsg_recv (frontend);
            if (!msg)
                break;

            zmsg_pushmem(msg, NULL, 0);
            zmsg_push(msg, (zframe_t *)zlist_pop(worker_queue));
            zmsg_send (&msg, backend);
            available_workers--;
        }
    }

    return 0;
}
