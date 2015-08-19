#include <event2/buffer.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static void
test_evbuffer_add_file ()
{
    struct evbuffer *evbuf;
    evbuf = evbuffer_new ();

    /* the file has "aaaaa", the @length param in evbuffer_add_file may not work. */
    int fd = open ("/tmp/aaa", O_RDONLY);
    evbuffer_add_file (evbuf, fd, 0, 4);
    char * buff = (char*)evbuffer_pullup (evbuf, 4);
    printf ("%s", buff);
    printf ("buffer length = %d\n", evbuffer_get_length (evbuf));
    assert (strcmp (buff, "aaaaa\n")==0);
}

/* every time, add/remove content from evbuffer will call it. */
static void
log_change_callback(struct evbuffer *buffer,
    const struct evbuffer_cb_info *cbinfo,
    void *arg)
{

	size_t old_len = cbinfo->orig_size;
	size_t new_len = old_len + cbinfo->n_added - cbinfo->n_deleted;
	struct evbuffer *out = arg;
	evbuffer_add_printf(out, "%lu->%lu; ", (unsigned long)old_len,
			    (unsigned long)new_len);
    printf ("enter log_change_callback\n");

}

void test_cb(struct evbuffer *buffer,
    const struct evbuffer_cb_info *cbinfo,
    void *arg)
{
    printf ("enter test_cb\n");
}


int main ()
{
    struct evbuffer *buf = evbuffer_new();
    struct evbuffer *buf_out1 = evbuffer_new();
    struct evbuffer *buf_out2 = evbuffer_new();
    struct evbuffer_cb_entry *cb1, *cb2;

    cb1 = evbuffer_add_cb(buf, log_change_callback, buf_out1);

    /* will call @test_cb first */
    cb2 = evbuffer_add_cb(buf, test_cb, buf_out2);


    evbuffer_add_printf(buf, "The %d magic words are spotty pudding", 2);
    /* disable callback */
    evbuffer_cb_clear_flags(buf, cb2, EVBUFFER_CB_ENABLED);
    evbuffer_drain(buf, 10); /*36->26*/
    evbuffer_prepend(buf, "Hello", 5);/*26->31*/

    /* enable callback */
    evbuffer_cb_set_flags(buf, cb2, EVBUFFER_CB_ENABLED);
    evbuffer_add_reference(buf, "Goodbye", 7, NULL, NULL); /*31->38*/

    /* remove callback from evbuff */
    evbuffer_remove_cb_entry(buf, cb2);
    evbuffer_drain(buf, evbuffer_get_length(buf)); /*38->0*/;

    /* another way to remove cb, NOTE, must be same with */
    assert(-1 == evbuffer_remove_cb(buf, log_change_callback, NULL));
    evbuffer_add(buf, "X", 1); /* 0->1 */
    assert(!evbuffer_remove_cb(buf, log_change_callback, buf_out1));
    evbuffer_add(buf, "X", 1); /* 0->1 */    
}
