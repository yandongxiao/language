#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    /* If you use "tcp://*:5555", you can connect on "tcp://localhost:5555" or "tcp://redhat-64:5555"
     * If you use "tcp://eth0:5555", you just can use "tcp://redhat-64:5555".
     * */
    void *socket = zmq_socket (contex, ZMQ_REP);
    int cc = zmq_bind (socket, "tcp://*:5555");
    assert (cc==0); 
    printf ("bind on server successfully\n");

    /*
     * If you remove the while on server and client, what will happened ?
     *    you must call zmq_close and zmq_ctx_destory at the end, or client or server will hang forever.   
     */
    while (1) {

        /*
         * recv message from client, the forth arguments is used to specify async or sync to recv.
         * NOTE: the difference of return value between zmq_recv and recv function
         */
        char buff[3];
        int len = zmq_recv (socket, buff, 3, 0);
        printf ("zmq_recv return %d\n", len);
        if (len<0) {    /* recv failed */
            printf ("errno=%d : %s\n", zmq_errno(), zmq_strerror(zmq_errno()));
            return -1;
        }
        if (len >= 3)  /* the len is the lenght of message frame, so we may get a truncated message */
            buff[2] = 0;
        else
            buff[len] = 0;

        /* zmq_recv will read a message frame each time, But there will be more message frames.
         * In this example, there is only one message frame in one message.
         */
        int more = 0;
        size_t more_len = sizeof(more);
        zmq_getsockopt (socket, ZMQ_RCVMORE, &more, &more_len);
        if (more)
            printf ("there is more message FRAME to recvive\n");
        else
            printf ("there is no message FRAME to recv\n");

        printf ("recv message : %s\n", buff);
        
        /* send a message back */
        sleep (1);
        zmq_send (socket, "world", 5, 0);
    }
    
    zmq_close (socket);
    zmq_ctx_destroy (contex);
    return 0;
}
