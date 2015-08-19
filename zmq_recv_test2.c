#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

char message [1024];

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    /* you can use ZMQ_REP and ZMQ_REQ as the parameter */
    void *socket = zmq_socket (contex, ZMQ_REP);
    int cc = zmq_connect (socket, "tcp://redhat-64:5555");
    assert (cc==0); 
    printf ("bind on server successfully\n");

    /* this is the manner how we read a message. */
    while  (1) {
        char buff[128];
        int len = zmq_recv (socket, buff, 128, 0);
        printf ("zmq_recv return %d\n", len);
        if (len<0) {
            printf ("errno=%d : %s\n", zmq_errno(), zmq_strerror(zmq_errno()));
            return -1;
        }
        if (len >= 128)
            buff[127] = 0;
        else
            buff[len] = 0;
       
        /* store the message first. */
        strcat (message, buff);

        int more = 0;
        size_t more_len = sizeof(more);
        zmq_getsockopt (socket, ZMQ_RCVMORE, &more, &more_len);
        if (!more)
            break;
    }

    printf ("recv message : %s\n", message);
    
    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
