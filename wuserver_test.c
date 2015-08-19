#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main ()
{
    void *contex = zmq_ctx_new ();
    assert (contex);

    void *socket = zmq_socket (contex, ZMQ_PUB);
    assert (socket);
    int cc = zmq_bind (socket, "tcp://*:5555");
    assert (cc==0);

    while (1) {
        char buff[128];
        scanf ("%s", buff);
        char string[256] = "100 ";
        strcat (string, buff);

        zmq_send (socket, string, strlen(string), 0);
        printf ("have send data to client\n");
        sleep (1);
    }

    return 0;
}
