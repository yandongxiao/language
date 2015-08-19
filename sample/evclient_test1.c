#include <string.h>
#include <errno.h>
#include <assert.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <netinet/in.h>
#include <event2/util.h>

/*
  * water mask, see evclient_test2
  */
void read_cb(struct bufferevent *bev, void *ctx)
{
    char buff[512];
    int len = bufferevent_read (bev, buff, 512);
    printf ("receive <%d> bytes: <%s>\n", len, buff);
}

void event_cb(struct bufferevent *bev, short what, void *ctx)
{
    printf ("event_cb\n");
    if (what & BEV_EVENT_ERROR) {
        printf ("receive an error <%s>\n", 
            evutil_socket_error_to_string (EVUTIL_SOCKET_ERROR()));
        bufferevent_free (bev);
    }
    else if (what & BEV_EVENT_CONNECTED) {
        printf ("connected to server\n");
    }

}

int main ()
{
    struct event_base *base;
    base = event_base_new();

    /*
        * create a bufferevent object used by client and server. 
        * now the bufferevent dose not bind a fd.
        */
    struct bufferevent *bev;
    bev = bufferevent_socket_new (base, -1, BEV_OPT_CLOSE_ON_FREE);
    assert (NULL != bev);

    /* 
        *  the server IP:port
        *  If there are errors, event_cb will receive a  <connection refused> error. 
        */
    struct sockaddr_in addr;
    memset (&addr, 0, sizeof(addr));    /* necessary */
    /* another way : addr.sin_addr.s_addr = htonl(0x7f000001) */
    evutil_inet_pton (AF_INET, "127.0.0.1", &addr.sin_addr);
    addr.sin_port = htons(8000);
    addr.sin_family = AF_INET;

    /*
        * it will create a fd which connect to the server. And bind it to @bev.
        */
    bufferevent_socket_connect (bev, (struct sockaddr *)&addr, sizeof(addr));


    /*
        * necessary for buffer event object. Or the connection will be broken once connect to server. 
        * If we only register the EV_READ callback, but we only pass the EV_WRITE. the connection will be broken too.
        */
    bufferevent_setcb (bev, read_cb, NULL, event_cb, NULL);
    bufferevent_enable (bev, EV_READ | EV_WRITE);


    
    event_base_dispatch (base);
    bufferevent_free (bev);
    event_base_free (base);
    return 0;
}
