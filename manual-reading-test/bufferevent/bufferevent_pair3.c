#include <event2/bufferevent.h>
#include <event2/event.h>
#include <assert.h>
#include <stdio.h>

struct event_base *bases[2];

struct bufferevent *pair[2];

void
read_func (struct bufferevent *bev, void *ctx)
{
    int i = 0;
    int len = bufferevent_read (bev, &i, sizeof(i));
    if (len >= 0)
        printf ("read value <%d>, len==%d\n", i, len);
}

void*
read_thread (void *arg)
{
    event_base_loop (bases[0], EVLOOP_NO_EXIT_ON_EMPTY);
}

void
write_func (struct bufferevent *bev, void *ctx)
{
    int val = 10;
    bufferevent_write (bev, &val, sizeof(val));
    sleep (1);
}

void*
write_thread (void *arg)
{
    event_base_loop (bases[1], EVLOOP_NO_EXIT_ON_EMPTY);
}

int main ()
{
    /* If you use libevent if multi-thread, you must initial it !! */
    evthread_use_pthreads();

    /* create event base */
    bases[0] = event_base_new ();
    bases[1] = event_base_new ();
    assert (NULL != bases[0]);
    assert (NULL != bases[1]);

    /* create bufferevent pair */ 
    int cc = bufferevent_pair_new (bases[0], 0, pair);
    assert (cc == 0);

    /* set pair[0] */
    bufferevent_base_set (bases[0], pair[0]);
    bufferevent_setcb (pair[0], read_func, NULL, NULL, NULL);
    bufferevent_enable (pair[0], EV_READ);

    /* set pair[1] */
    bufferevent_base_set (bases[1], pair[1]);
    bufferevent_setcb (pair[1], NULL, write_func, NULL, NULL);
    bufferevent_enable (pair[1], EV_WRITE);

    bufferevent_trigger (pair[1], EV_WRITE, 0);

    pthread_t thread;
    pthread_create (&thread, NULL, write_thread, NULL);
    pthread_create (&thread, NULL, read_thread, NULL);

    pthread_join(thread, NULL);
    return 0;
}
