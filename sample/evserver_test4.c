#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include <event2/listener.h>
#include <event2/bufferevent.h>


/* error test for bufferevent_pair_new */

int badtest ()
{
    struct event_base *base;
    base = event_base_new ();
    
    struct bufferevent *pair [2];
    int cc = bufferevent_pair_new (base, 0, pair);
    assert (cc == 0);

 //   bufferevent_setcb (struct bufferevent * bufev,bufferevent_data_cb readcb,bufferevent_data_cb writecb,bufferevent_event_cb eventcb,void * cbarg)
    pid_t pid = fork ();
    if (pid > 0) {
        sleep (2);
        char buff[512];
        int len = bufferevent_read (pair[0], buff, 512);
        buff[len] = '\0';
        printf ("read <%d> data : %s\n", len, buff);
        wait(NULL);
    }
    else if (pid==0) {
        bufferevent_write (pair[1], "hello", strlen("hello"));
    }

    return 0;
}

struct event_base *base;
struct bufferevent *pair [2];

void
write_cb (struct bufferevent *bev, void *ctx)
{
    char buff[512];
    
    fgets (buff, 512, stdin);
    int len = strlen(buff);
    buff [len-1] = '\0';

    bufferevent_write (bev, buff, len);

}

void read_cb(struct bufferevent *bev, void *ctx)
{
    char buff[512];
    int len = bufferevent_read (bev, buff, 512);
    buff[len] = '\0';
    printf ("read <%d> bytes : <%s>", len, buff);
}

void *
thread_cb (void* arg)
{
    bufferevent_setcb (pair[0], read_cb, NULL, NULL, NULL);
    bufferevent_enable (pair[0], EV_READ);

    bufferevent_setcb (pair[1], NULL, write_cb, NULL, NULL);
    bufferevent_enable (pair[1], EV_WRITE);

    int cc = event_base_dispatch (arg);
    printf ("cc == %d\n", cc);
    return NULL;
}

int 
main (void)
{
    base = event_base_new ();

    /* evutil_socketpair */
    int cc = bufferevent_pair_new (base, BEV_OPT_CLOSE_ON_FREE, pair);
    assert (cc == 0);
    struct bufferevent *bev = bufferevent_pair_get_partner (pair[0]);
    assert (bev == pair[1]);


//    bufferevent_setcb (pair[0], read_cb, write_cb, NULL, NULL);
//    bufferevent_enable (pair[0], EV_READ | EV_WRITE );

    bufferevent_setcb (pair[1], read_cb, NULL, NULL, NULL);
    bufferevent_enable (pair[1], EV_READ);

    cc = event_base_dispatch (base);
    printf ("cc == %d\n", cc);

//    bufferevent_write (pair[1], "hello", strlen("hello"));
    printf ("done\n");
    return 0;
}

