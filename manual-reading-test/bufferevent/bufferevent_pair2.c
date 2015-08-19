#include <event2/bufferevent.h>
#include <event2/event.h>
#include <assert.h>
#include <stdio.h>

struct event_base *base;

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
write_thread (void *arg)
{
    int val = 1;
    while (1) {
        /*every write, will create a pending event and active it */
        int cc = bufferevent_write (pair[1], &val, sizeof(val));
        assert (cc == 0);
        val++;
        sleep (1);
    }
}

int main ()
{
    /* If you use libevent if multi-thread, you must initial it */
    evthread_use_pthreads();

    /* create event base */
    base = event_base_new ();
    assert (NULL != base);

    /* create bufferevent pair */ 
    /* should we use BEV_OPT_ThREADSAFE ? no, only one thread write. */
    int cc = bufferevent_pair_new (base, 0, pair);
    assert (cc == 0);

    /* set callback */
    bufferevent_setcb (pair[0], read_func, NULL, NULL, NULL);
    bufferevent_enable (pair[0], EV_READ);

    pthread_t thread;
    pthread_create (&thread, NULL, write_thread, NULL);
  
//    event_base_loop (base, EVLOOP_NO_EXIT_ON_EMPTY);


    /* If data has written to pair[0], invoke callback
     * then, check wether there are data in pair[0]. 
     * If nothing, that is not pending event, return
     */
    /* add sleep for test */
    sleep (3);
    event_base_dispatch (base);   /* It will return write now */

    return 0;
}
