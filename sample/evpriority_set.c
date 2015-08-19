#include <event2/event.h>
#include <stdio.h>

void
event_cb1(evutil_socket_t fd,short events,void *arg)
{
    printf ("event 1 called\n");
}

void
event_cb2(evutil_socket_t fd,short events,void *arg)
{
    printf ("event 2 called\n");
}

void
event_cb3(evutil_socket_t fd,short events,void *arg)
{
    printf ("event 3 called\n");
}


/*
 *
 * there are two level event. NONONO, there are only event priority.
 * the event_base_priority_init specify the max priority value.
 * 
 * event_priority_set
 *
 * The priority of the event is a number between 0 and the number of 
 * priorities in an event_base, minus 1. 
 * The function returns 0 on success, and -1 on failure.
 * 
 * 0 has the highest pri.
 *
 * Note:
 *       event_base_priority_init is necessary for us.
 *       there is no meanning to compare two event_base priority, has no such API
 * 
 */
int test_event_pri (void)
{
    struct event_base *base = event_base_new ();
    /**/
    event_base_priority_init (base, 10);
    struct event *ev1 = event_new (base, -1, 0, 
                        event_cb1, event_self_cbarg());
    struct event *ev2 = event_new (base, -1, 0, 
                        event_cb2, event_self_cbarg());
    struct event *ev3 = event_new (base, -1, 0, 
                        event_cb3, event_self_cbarg());

    event_priority_set (ev2, 1);

    event_priority_set (ev1, 0);
    event_priority_set (ev3, 3);


    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add (ev1, &tv);
    event_add (ev2, &tv);
    event_add (ev3, &tv);

    event_base_dispatch (base);
    return 0;
}

int main ()
{
    test_event_pri();
    return 0;
}
