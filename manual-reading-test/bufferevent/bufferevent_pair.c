#include <event2/bufferevent.h>
#include <event2/event.h>
#include <assert.h>
#include <stdio.h>

struct event_base *base;

struct bufferevent *pair[2];

void
read_func (struct bufferevent *bev, void *ctx)
{
    int i;
    bufferevent_read (bev, &i, sizeof(i));
    printf ("read value <%d>\n", i);
}

void
write_func (struct bufferevent *bev, void *ctx)
{
    printf ("have written to client\n");
}

void
event_cb (struct bufferevent *bev, short what, void *arg)
{
    /* no event happened */
    printf ("%s\n", __func__);
}

int main ()
{
    int cc;

    /* create event base */
    base = event_base_new ();
    assert (NULL != base);

    /* create bufferevent pair */ 
    cc = bufferevent_pair_new (base, 0, pair);
    assert (cc == 0);

    /* set callback */
    bufferevent_setcb (pair[0], read_func, NULL, event_cb, NULL);
    bufferevent_setcb (pair[1], NULL, write_func, event_cb, NULL);

    /* you must set all of them */
    bufferevent_enable (pair[0], EV_READ);

    /* create two event that call read_func and write_func at last */
    int val=10;
    bufferevent_write (pair[1], &val, sizeof(val));

    /* After execute the above two event, return */
    event_base_dispatch (base);

    return 0;
}
