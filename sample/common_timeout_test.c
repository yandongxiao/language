#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
  * there are @num events at the same time. delay is:
  *
  * 200 events   --> 0 --0.2  ms
  * 2000 events --> 0 --10 ms (core dump some time)
  * 20000 events  core dump
  *
  */

int s_num = 1;
struct timeval lasttime;
#define EVNETS_NUM 1000

void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    /* 1..EVNETS_NUM-1 */
    if (s_num < EVNETS_NUM) {
        if (s_num==1) {
            evutil_gettimeofday(&lasttime, NULL);
        }
        s_num++;
        return;
    }

    struct timeval now, sub;
    evutil_gettimeofday (&now, NULL);
    evutil_timersub (&now, &lasttime, &sub);
    
    printf ("event cb called apart : <%llu>(us)\n", (unsigned long long)sub.tv_sec*1000*1000+sub.tv_usec);
    s_num=1;
}

void
sig_int (evutil_socket_t fd,short events,void *arg)
{
    struct event_base *base = arg;
    event_base_loopbreak (base);
}

int
main (int argc, char **argv)
{
    struct event_base *base = event_base_new ();

    struct event *evs[20];
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    /* I do not find the effect.
        * But you should find that 
        * This optimization probably will not be worthwhile until you have thousands or tens of thousands of events with the same timeout.
        */
//    struct timeval *duration = event_base_init_common_timeout (base, &tv);
    int i=0;
    for (i=0; i<EVNETS_NUM; i++) {
        evs[i] = event_new (base, -1, EV_PERSIST, event_cb, event_self_cbarg());
//        event_add (evs[i], duration);        
        event_add (evs[i], &tv);
    }

    struct event *sigev = evsignal_new (base, SIGINT, sig_int, base);
    event_add (sigev, NULL);
    event_base_dispatch (base);

    for (i=0; i<EVNETS_NUM; i++) {
        event_del(evs[i]);
        event_free (evs[i]);
    }
    event_base_free (base);

    return 0;
}



