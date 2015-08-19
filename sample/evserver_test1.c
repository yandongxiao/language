#include <event2/listener.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void listener_cb (struct evconnlistener *listener, 
                                    evutil_socket_t fd,
                                    struct sockaddr *addr, 
                                    int socklen, 
                                    void *arg)
{
    printf ("receive a connection\n");
}
                                    


int main (void)
{
    /*
        * step 1 : create a struct event_base object.
        */
    struct event_base *base;
    base = event_base_new ();

    /*
        * step 2 : create the server listener socket.
        */
    evutil_socket_t listenfd;
    listenfd = socket (AF_INET, SOCK_STREAM, 0);
    assert (listenfd > 0);

    /*
        * step 3 : bind the address.
        */
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8080);
    int cc = bind (listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    assert (cc == 0);

    /*
        * set socket option, by evutil_* fucntion.
        */
    evutil_make_socket_closeonexec (listenfd);
    evutil_make_socket_nonblocking (listenfd);

    evconnlistener_new (base, listener_cb, NULL, 
                       LEV_OPT_CLOSE_ON_EXEC, 32, listenfd);

    event_base_dispatch (base);
}
