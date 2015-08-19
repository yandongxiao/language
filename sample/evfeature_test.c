#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    printf ("event cb called\n");
}

int
main (int argc, char **argv)
{
    
    struct event_base *base = event_base_new ();

    /* use epoll as libevent backend default. */
    printf("Using Libevent with backend method %s.",
        event_base_get_method(base));

    /* support EV_FEATURE_ET and EV_FEATURE_O1 feature. */
    int features = event_base_get_features(base);
    if (features & EV_FEATURE_ET)
        printf ("support EV_ET event\n");
    if (features & EV_FEATURE_O1)
        printf ("support have one event triggered among many is an O(1) operation \n");

    /* 要求支持任意文件描述符，而不仅仅是套接字的后端 */
    if (features & EV_FEATURE_FDS)
        printf ("support allows file descriptors as well as sockets");

    event_base_free (base);
    return 0;
}



