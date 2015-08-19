#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


/*
  * event_base_loop has more flexbility than event_base_dispatch.
  * But the functionality of them is totoally different.
  */
void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    printf ("event cb called\n");
}

int
main (int argc, char **argv)
{
    
    struct event_base *base = event_base_new ();
    struct event *ev = event_new (base, STDIN_FILENO, EV_READ, event_cb, NULL);
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    event_add (ev, &tv);

    /*
        * Block until we have an active event
        * then exit once the event had their callbacks run
        */
    event_base_loop (base, EVLOOP_ONCE);

    /*
        * EVLOOP_NONBLOCK
        * no active events, so it will exit immediately.
        */
//    int cc = event_base_loop (base, EVLOOP_NONBLOCK);
//    assert (0 == cc);

    /*
        * event there are no pending events, still waiting.
        * 
        */
    int cc = event_base_loop (base, EVLOOP_NO_EXIT_ON_EMPTY);
    assert (0 == cc);
    
    event_free (ev);
    event_base_free (base);
    return 0;
}


