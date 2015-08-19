#include <errno.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <string.h>

/*
  * this is a client, you need a server running first.
  * 
  *
  */

void eventcb(struct bufferevent *bev, short events, void *ptr)
{
    if (events & BEV_EVENT_CONNECTED) {
         /* We're connected to 127.0.0.1:8080.   Ordinarily we'd do
            something here, like start reading or writing. */
        printf ("conneced\n");
    } else if (events & BEV_EVENT_ERROR) {
         /* An error occured while connecting. */
        printf ("error whhile conneced : %s\n", evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR()));
    }
}

int 
main(void)
{
    struct event_base *base;
    struct bufferevent *bev;
    struct sockaddr_in sin;

    base = event_base_new();

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0x7f000001); /* 127.0.0.1 */
    sin.sin_port = htons(8080); /* Port 8080 */

    /*
        * 1. there is no bufferevent_new routine, only bufferevent_socket_new can create a bufferevent object.
        * 2. bufferevent can only work with file descriptor(exclude pipe).
        * 3. BEV_OPT_*
        * 4. no callback setting.
        */
    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    /*
        * when eventcb called ? see BEV_EVENT_* for more infomation.
        */
    bufferevent_setcb(bev, NULL, NULL, eventcb, NULL);

    /*
        * 1. set the file descriptor to bufferevent object.
        * 2. connect to server.
        */
    if (bufferevent_socket_connect(bev,
        (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        /* Error starting connection */
        bufferevent_free(bev);
        return -1;
    }

    event_base_dispatch(base);
    return 0;
}

