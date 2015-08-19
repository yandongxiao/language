#include <assert.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/bufferevent_struct.h>
#include <event.h>

static int test_ok;

static void
readcb(struct bufferevent *bev, void *arg)
{
#if 0
	if (evbuffer_get_length(bev->input) == 8333) {
		struct evbuffer *evbuf = evbuffer_new();
		assert(evbuf != NULL);

		/* gratuitous test of bufferevent_read_buffer */
		bufferevent_read_buffer(bev, evbuf);

		bufferevent_disable(bev, EV_READ);

		if (evbuffer_get_length(evbuf) == 8333) {
			test_ok++;
		}

		evbuffer_free(evbuf);
	}
#endif
    printf ("enter cb");
}

static void
writecb(struct bufferevent *bev, void *arg)
{
	if (evbuffer_get_length(bev->output) == 0) {
		test_ok++;
	}
}

static void
errorcb(struct bufferevent *bev, short what, void *arg)
{
	test_ok = -2;
}

int
main ()
{
	struct bufferevent *bev1 = NULL, *bev2 = NULL;
	char buffer[8333];
	int i;

	struct bufferevent *pair[2];
	assert(0 == bufferevent_pair_new(NULL, 0, pair));
	bev1 = pair[0];
	bev2 = pair[1];
	bufferevent_setcb(bev1, readcb, writecb, errorcb, bev1);
	bufferevent_setcb(bev2, readcb, writecb, errorcb, NULL);
	assert(bufferevent_getfd(bev1) == -1);
	assert(bufferevent_get_underlying(bev1) == NULL);
	assert(bufferevent_pair_get_partner(bev1) == bev2);
	assert(bufferevent_pair_get_partner(bev2) == bev1);

	{
		/* Test getcb. */
		bufferevent_data_cb r, w;
		bufferevent_event_cb e;
		void *a;
		bufferevent_getcb(bev1, &r, &w, &e, &a);
		assert(r == readcb);
		assert(w == writecb);
		assert(e == errorcb);
		assert(a == bev1);
	}

	bufferevent_disable(bev1, EV_READ);
	bufferevent_enable(bev2, EV_READ);

	assert(bufferevent_get_enabled(bev1) == EV_WRITE);
	assert(bufferevent_get_enabled(bev2) == (EV_WRITE|EV_READ));

	for (i = 0; i < (int)sizeof(buffer); i++)
		buffer[i] = i;

//	bufferevent_write(bev1, buffer, sizeof(buffer));

//	event_dispatch();

	bufferevent_free(bev1);
//	assert(bufferevent_pair_get_partner(bev2) == NULL);
	bufferevent_free(bev2);

	if (test_ok != 2)
		test_ok = 0;

    return 0;
}


