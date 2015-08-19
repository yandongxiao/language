#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>

/* fro valgrind test */
struct event_base *base;
struct event *ev;

struct timeval lasttime;
int event_is_persistent;

/* for compatable, we use eventsignal stread of liux signal. */
/* try to use event_base_loopbreak to terminal normally. */
void
sig_int (evutil_socket_t fd, short events, void *arg)
{
    event_is_persistent = 0;
    event_del (ev);
    event_del (arg);
}

void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    struct event *ev = arg;
    struct timeval nowtime;
    struct timeval subtime;
    
    evutil_gettimeofday(&nowtime, NULL);
    evutil_timersub (&nowtime, &lasttime, &subtime);
    lasttime = nowtime;

    printf("timeout_cb called %.3f elapsed.\n", subtime.tv_sec + subtime.tv_usec/1.0e6);
   
    if (! event_is_persistent) {
        struct timeval tv;
        evutil_timerclear(&tv);
        tv.tv_sec = 2;

        /* you can add event in event_cb. */
        event_add (ev, &tv); 
    }

}


int
main (int argc, char **argv)
{
    struct event *sigev;
    short events;
    struct timeval tv;
    if (argc==2) {
        event_is_persistent = 1;
        events = EV_PERSIST;
    }
    else {
        event_is_persistent = 0;
        events = 0;
    }

    base = event_base_new ();

    ev = event_new (base, 0, events, event_cb, event_self_cbarg());
    evutil_timerclear(&tv);
    tv.tv_sec = 2;
    event_add (ev, &tv);

    sigev = evsignal_new (base, SIGINT, sig_int, event_self_cbarg());
    evsignal_add (sigev, NULL);

    evutil_gettimeofday(&lasttime, NULL);
    event_base_dispatch (base);

    event_free (sigev);
    event_free (ev);
    event_base_free (base);

    return 0;
}
