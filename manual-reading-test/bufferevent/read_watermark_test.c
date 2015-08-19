#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#define SVRADDR "127.0.0.1"
#define PORT 8080

FILE *ff;

struct event_base *p_base;

struct bufferevent *p_event;

/* verify the work manner of water-mark */
void eventcb(struct bufferevent *bev, short events, void *ptr)
{
    printf ("eventcb called\n");
}

static void
buff_input_cb (struct bufferevent *bev,
               void *ctx)
{
    printf("%s called\n", __func__);

    int len = evbuffer_get_length(bufferevent_get_input(bev));
    printf("len=%d\n", len);
    event_base_dump_events(p_base, ff);

    if (len==20) {
        char buff[1024];
        /* first read data, second make READ event pending */
        /* If you coment it, program will exit */
        //bufferevent_read(bev, buff, 1024);
        len = evbuffer_get_length(bufferevent_get_input(bev));
        printf("len=%d\n", len);
        event_base_dump_events(p_base, ff);
    }

    return;
}

static void
buff_ev_cb (struct bufferevent *bev,
            short events,
            void *ctx)
{

    printf("in %s\n", __func__);

    if (events & BEV_EVENT_CONNECTED) {
        printf("***BEV_EVENT_CONNECTED\n");
    }else if (events & BEV_EVENT_ERROR) {
        printf("***BEV_EVENT_ERROR\n");
    }else if (events & BEV_EVENT_EOF) {
        printf("***BEV_EVENT_EOF\n");
    }
    return;
}

void
do_init ()
{
    int sockfd;
    struct sockaddr_in addr;

    ff = fopen("/tmp/log", "w");
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SVRADDR, &addr.sin_addr) <= 0) {
        printf("inet_pton");
        exit(1);
    }

    if ((p_base = event_base_new()) == NULL) {
        printf("event_base_new ");
        return; 
    }

    /* we do not need invoke socket function to create socket */
    /* BEV_OPT_DEFER_CALLBACKS dose not make dispatch exit */
    if ((p_event = bufferevent_socket_new(p_base, -1, BEV_OPT_CLOSE_ON_FREE)) == NULL) {
        printf("bufferevent_socket_new ");
        return;
    }

    /* client actually connecte to server at this time. */
    if ((sockfd = bufferevent_socket_connect(p_event, (struct sockaddr *) &addr,
                                             sizeof(addr))) < 0) {
        printf("bufferevent_socket_connect ");
        return;
    }
}

int
main ()
{
    do_init();

    /* EV_WRITE is default enabled, EV_READ is default disabled */
    bufferevent_setcb(p_event, buff_input_cb, NULL, eventcb, p_base);
    bufferevent_enable(p_event, EV_READ);

    /* edge-triggered */
    /* default read low-water  mark is 0. */
    /* default read high-water mark is unlimited. */
    /* If the underlying data received over 20, remove the READ event from base */
    bufferevent_setwatermark(p_event, EV_READ, 10, 20);

    /* no exit */
    event_base_dispatch(p_base);

    return 0;
}
