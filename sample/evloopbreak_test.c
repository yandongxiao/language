
#include <event2/event.h>

void
event_cb (evutil_socket_t fd, short events, void *arg)
{
    printf ("event_cb called\n");
    struct event_base *base = arg;

    /*
        * if the event_base is currently running callbacks for any active events, 
        * it will exit immediately after finishing the one it¡¯s currently processing.
        * Note : the current cb done.
        *
        */
    event_base_loopbreak (base);

    /* If the event_base is currently running callbacks for any active events, 
        * it will continue running them, and not exit until they have all been run.
        * Note: all active event.
        */
//    event_base_loopexit (base, NULL);
}


int main (void)
{
    struct event_base *base = event_base_new ();
    struct event *ev1 = event_new (base, -1, EV_PERSIST, event_cb, base);
    struct event *ev2 = event_new (base, -1, EV_PERSIST, event_cb, base);

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add (ev1, &tv);
    event_add (ev2, &tv);    

    event_active (ev1, EV_TIMEOUT, 0);
    event_active (ev2, EV_TIMEOUT, 0);

    event_base_dispatch (base);

    event_free (ev1);
    event_free (ev2);    
    event_base_free (base);
}


