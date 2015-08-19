#include <event2/event_compat.h>
#include <event2/event.h>
#include <assert.h>

void
event_cb (evutil_socket_t fd, short events, void *arg)
{
    printf ("event_cb called\n");

    /* to verify the event_base_got_exit, we try to use
        * event_base_loppexit first, cc=0
        * second, use event_loopexit secondly, the program core dump.
        * 
        * So, do use it now.
        */

    //event_loopexit (NULL);
    int cc = event_base_got_exit (arg);
    printf ("cc == %d\n", cc);
    //assert(cc == 1);    
}


int main (void)
{
    struct event_base *base = event_base_new ();
    struct event *ev1 = event_new (base, -1, EV_PERSIST, event_cb, base);


    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add (ev1, &tv);


//    event_active (ev1, EV_TIMEOUT, 0);

    /* have no effect. */
//    event_base_loopbreak (base);

    /*
        * loopexit schedules the next instance of the event loop to
        * stop right after the next round of callbacks are run 
        * (as if it had been invoked with EVLOOP_ONCE) whereas 
        * loopbreak only stops a currently running loop, and has no
        * effect if the event loop isn¡¯t running.
        */

     /*
         * when where is no active event, event_base_dispatch will like EVLOOP_NONBLOCK
         */
//    event_base_loopexit (base, NULL);
    event_base_dispatch (base);

    event_free (ev1);
    event_base_free (base);
}


