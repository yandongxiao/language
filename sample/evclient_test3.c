#include <string.h>
#include <errno.h>
#include <assert.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <netinet/in.h>
#include <event2/util.h>

/*
  * water mask, see evclient_test2
  */
void read_cb(struct bufferevent *bev, void *ctx)
{
    char buff[512];
    int len = bufferevent_read (bev, buff, 512);
    buff[len] = '\0';
    printf ("receive <%d> bytes: <%s>\n", len, buff);

    /* It make effective to underlying transport.
        * Flushing a bufferevent tells the bufferevent to force 
        * as many bytes as possible to be read to or written from the underlying transport, 
        * ignoring other restrictions that might otherwise keep them from being written. 
        */
    //bufferevent_flush (bev, EV_READ, BEV_NORMAL);
    short events = bufferevent_get_enabled (bev);
    assert (events & EV_READ);
    assert (events & EV_WRITE);
}

void event_cb(struct bufferevent *bev, short what, void *ctx)
{
    /* you can only use evutil_socket_error_to_string to BEV_EVENT_ERROR events. */
    if (what & BEV_EVENT_ERROR) {
        printf ("event error <%s>\n", 
            evutil_socket_error_to_string (EVUTIL_SOCKET_ERROR()));
        event_base_loopexit (bufferevent_get_base(bev), NULL);
    }
    else if (what & BEV_EVENT_CONNECTED) {
        printf ("connected to server\n");
    }
    else if (what & BEV_EVENT_EOF) {
        /* happened when server exit. */
        printf ("read to the end of EOF\n");
        event_base_loopexit (bufferevent_get_base(bev), NULL);
    }
    else if (what & BEV_EVENT_READING) {
        printf ("error while reading\n");
    }
    else if (what & BEV_EVENT_WRITING) {
        printf ("error while writing\n");
    }

}

int main ()
{
    struct event_base *base;
    base = event_base_new();
    assert (NULL != base);
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

    /*
        * you input "PP" "PP",  client will read all of them
        * you input "PPP" "PPP", every time you put client will read them, 
        * you input "pppp",  "tttt",  every time you put client will read them, 
        * you input "pppppp", client will read the first 5 bytes. leave the last one. 
        */
    bufferevent_setwatermark (bev, EV_READ, 3, 5);

    bufferevent_enable (bev, EV_READ | EV_WRITE);

    event_base_dispatch (base);
    
    bufferevent_free (bev);
    event_base_free (base);
    return 0;
}
