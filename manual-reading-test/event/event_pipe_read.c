#include <event2/event.h>
#include <pthread.h>

int fd[2];

void*
thread_cb (void *arg)
{
    close (fd[1]);
}

void
event_cb (evutil_socket_t sock, short what, void *arg)
{
    printf ("%s called\n", __func__);

}

int main ()
{
    struct event_base *base = event_base_new ();
    pipe (fd);

    struct event *ev = event_new (base, fd[0], EV_READ | EV_PERSIST, event_cb, NULL);
    event_add (ev, NULL);

    pthread_t thread;
    pthread_create (&thread, NULL, thread_cb, NULL);
    event_base_dispatch(base);
}
