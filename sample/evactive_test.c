#include <event2/event.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void
event_cb(evutil_socket_t fd,short events,void *arg)
{
    printf ("event cb called\n");
}


int
main (int argc, char **argv)
{
    
    struct event_base *base = event_base_new ();

    /*
        * once you call a Libevent function to set up an event and associate 
        * it with an event base, it becomes initialized. 
        *
        * default it will be waitting all the time.
        */
    struct event *ev = event_new (base, STDIN_FILENO, EV_READ, event_cb, NULL);

    /*
        * call event_add, which makes it pending in the base.
        * If the event is configured persistent, it remains pending. 
        * If it is not persistent, it stops being pending when its callback runs.
        */
//    event_add (ev, NULL);

    /*         
        * if the conditions that would trigger an event occur, e.g. its file descriptor changes state or its timeout expires
        * the event becomes active.
        * when work done, set the event state to the original one. So ev has EV_PERSISTED flag, has no effect when not added..
        *
        * Note: event the above event_add is commented, its call back will be executed.
        * You can use this function on a pending or a non-pending event to make it active
        * One common use in multithreaded programs is to wake the thread running event_base_loop() from another thread.
        */
    event_active (ev, EV_READ, 0);
    event_base_dispatch (base);

    event_free (ev);
    event_base_free (base);

    return 0;
}

