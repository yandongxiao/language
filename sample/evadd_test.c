#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct timeval lasttime;
int s_cnt = 0;

void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    struct timeval now, sub;
    struct event *ev = arg;
    evutil_gettimeofday (&now, NULL);

    evutil_timersub (&now, &lasttime, &sub);
    lasttime = now;

    printf ("event cb called after : %.3f\n", sub.tv_sec+sub.tv_usec/1.0e6);
    
    if (s_cnt >= 3) {
        struct timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        /*
              * If the event in the ev argument already has a scheduled timeout
              * calling event_add() replaces the old timeout with the new one, or clears the old timeout.
              */
        event_add (ev, &tv);
    }
    s_cnt++;
}


int
main (int argc, char **argv)
{
    
    struct event_base *base = event_base_new ();

    struct event *ev = event_new (base, -1, EV_PERSIST, event_cb, event_self_cbarg());

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add (ev, &tv);

    evutil_gettimeofday (&lasttime, NULL);
    event_base_dispatch (base);

    event_free (ev);
    event_base_free (base);

    return 0;
}


