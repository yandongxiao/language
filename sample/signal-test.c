#include <event2/event.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

static int s_sigcnt = 0;

/*
  * fd : is a file descriptor or signal.
  * events : one or more EV_* flags.
  */
void
sig_int (evutil_socket_t fd, short events, void *arg)
{
    assert (events == EV_SIGNAL);
    struct event *ev = (struct event *)arg;
    int signal = event_get_signal(ev);
    assert (fd == SIGINT);
    if (s_sigcnt >= 2) {
        /* so, we do not need call event_free ? */
        event_del(ev);
    }
    printf ("caught signal <%s>\n", strsignal(signal));
    s_sigcnt++;
}

int
main (void)
{
    /* step 1: initialize the libevent library. */
    struct event_base *base;
    base = event_base_new();

    /* step 2 : Initialize an event. */
    struct event *ev;
    /* even the @ev has not been created, you can use it as parameters. */
    /* evsignal_new is a macro, we'd better use it. to understand easily. */
    ev = evsignal_new (base, SIGINT, sig_int, event_self_cbarg());

    /* step 3 : add an event to the set of pending events. */
    /* NULL tell us will waitting forever. */
    event_add (ev, NULL);

    /* run it */
    event_base_dispatch (base);
    
    /* the created event and vent base need be freed. */
    event_free (ev);
    event_base_free (base);
    return 0;
}

