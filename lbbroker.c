#include <stdio.h>
#include <zmq.h>
#include "zhelpers.h"
#include <pthread.h>
#include <unistd.h>

#define NBR_CLIENTS 30
#define NBR_WORKERS 3

#define DEQUEUE(q) memmove (&(q)[0], &(q)[1], sizeof (q) - sizeof (q [0]))

static void*
client_task(void *arg)
{
    void* ctx = zmq_ctx_new ();
    void *client = zmq_socket (ctx, ZMQ_REQ);
    zmq_setsockopt (client, ZMQ_IDENTITY, arg, strlen (arg));
    zmq_connect (client, "tcp://localhost:5555");
    
    while (1) {
        char buff[128];
        sprintf (buff, "hi, i am client <%s>", arg);
        s_send (client, buff);
        char *reply = s_recv (client);
        printf ("%s: get reply\n\n\n", arg);
        free (reply);

        sleep (1);
    }
}

static void*
worker_task(void *arg)
{
    void* ctx = zmq_ctx_new ();
    void *worker = zmq_socket (ctx, ZMQ_REQ);
    zmq_setsockopt (worker, ZMQ_IDENTITY, arg, strlen (arg));
    zmq_connect (worker, "tcp://localhost:6666");

    s_send (worker, "ready");

    while (1) {
        char *identity = s_recv (worker);
        char *delimiter = s_recv (worker);
        char *request = s_recv (worker);
        printf ("%s: get request from <%s>\n", arg, identity);
        free (request);
        
        char buff[128];
        sprintf (buff, "hi, i am client <%s>", arg);
        s_sendmore(worker, identity);
        s_sendmore(worker, delimiter);
        s_send (worker, buff);
    }
}

int main ()
{
    void *ctx = zmq_ctx_new ();
    void *frontend = zmq_socket (ctx, ZMQ_ROUTER);
    void *backend = zmq_socket (ctx, ZMQ_ROUTER);
    zmq_bind (frontend, "tcp://*:5555");
    zmq_bind (backend,  "tcp://*:6666");

    int client_nbr; 
    for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++) {                                
        pthread_t client;
        char *buff = malloc (128);
        sprintf(buff, "client%d", client_nbr);
        pthread_create(&client, NULL, client_task, buff);                 
    }
    
    int worker_nbr; 
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++) {                                
        pthread_t worker;
        char *buff = malloc (128);
        sprintf(buff, "worker%d", worker_nbr);
        pthread_create(&worker, NULL, worker_task, buff);                 
    }
   int available_workers = 0;
   char *worker_queue[NBR_WORKERS];
   while (1) {
        zmq_pollitem_t items[] = {
                     { backend, 0, ZMQ_POLLIN, 0 },
                     { frontend, 0, ZMQ_POLLIN, 0 }
                     };
        
        int rc = zmq_poll (items, available_workers? 2:1, -1);
        if (rc==-1)
            break;
        
        if (items[0].revents & ZMQ_POLLIN) {

            char *worker_id = s_recv (backend);
            worker_queue[available_workers] = worker_id;
            available_workers++;

            char *delimiter = s_recv (backend);
            free (delimiter);

            char *contents = s_recv (backend);
            if (strcmp(contents, "ready") != 0) {
                printf ("proxy: get a reply from worker <%s>, send to client <%s>\n", worker_id, contents);
                char *client_id = contents;
                char *delimiter = s_recv (backend);
                contents = s_recv(backend);

                s_sendmore (frontend, client_id);
                s_sendmore (frontend, delimiter);
                s_send (frontend, contents);

                free (delimiter);
                free (contents);
                free (client_id);
            } else {
                printf ("proxy: there is a new worker\n");
            }
        }

        if (items[1].revents & ZMQ_POLLIN) {
            char *client_id = s_recv (frontend);
            char *delimiter = s_recv (frontend);
            char *request = s_recv (frontend);

            printf ("proxy: get a request from client <%s>, send to <%s>\n", client_id, worker_queue[0]);
            
            s_sendmore (backend, worker_queue[0]);
            s_sendmore (backend, delimiter);
            s_sendmore (backend, client_id);
            s_sendmore (backend, delimiter);
            s_send (backend, request);

            free (worker_queue[0]);
            DEQUEUE (worker_queue);
            free (client_id);
            free (delimiter);
            free (request);

            available_workers--;
        }
    }

    return 0;
}
