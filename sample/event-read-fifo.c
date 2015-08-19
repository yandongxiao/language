/*
 * this dose not work on windows. 
 * libevent dose not do any work about it.
 */
#include <event2/event.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static void
fifo_read(evutil_socket_t fd, short event, void *arg)
{
    char buf[255];
    int len;
    struct event *ev = arg;

    fprintf (stderr, "events is <%s>\n", strevent (event));
    len = read(fd, buf, sizeof(buf) - 1);

    /* Connection closed. */
    if (len==0) {
        fprintf(stderr, "Connection closed\n");
        event_base_loopbreak(event_get_base(ev));
        return;
    }
    else if (len <= 0) {
        perror ("read");
        event_base_loopbreak(event_get_base(ev));
        return;
    }
    
    buf[len] = '\0';
    fprintf(stdout, "Read: %s\n", buf);
}

static void
signal_cb(evutil_socket_t fd, short event, void *arg)
{
    struct event_base *base = arg;
    event_base_loopbreak(base);
}

int
main(int argc, char **argv)
{
    struct event *evfifo;
    struct event_base* base;
    struct event *signal_int;
    int socket;

    /* fifo can not be created on mounted fs. */
    const char *fifo = "/tmp/event.fifo";
    struct stat st;

    /* normally, it is impposible. */
    if (lstat(fifo, &st) == 0) {
        if (! S_ISFIFO (st.st_mode)) {
            /* the error string will be : FILE EXIST */
            errno = EEXIST;
            perror("mkfifo");   
            exit(1);
        }
    }
    unlink(fifo);

    if (mkfifo(fifo, 0600) == -1) {
        perror("mkfifo");
        exit(1);
    }

    /* it has not effect, when setting O_NONBLOCK */
    socket = open(fifo, O_RDONLY);
    if (socket == -1) {
        perror("open");
        exit(1);
    }

    fprintf(stderr, "Write data to %s\n", fifo);

    /* Initalize the event library */
    base = event_base_new();
    
    /* catch SIGINT so that event.fifo can be cleaned up */
    signal_int = evsignal_new(base, SIGINT, signal_cb, base);
    event_add(signal_int, NULL);

    /* detect the read_fifo event. */
    evfifo = event_new(base, socket,
                       EV_READ|EV_PERSIST, 
                       fifo_read,
                       event_self_cbarg());
    event_add(evfifo, NULL);

    event_base_dispatch(base);

    event_base_free(base);
    event_free (signal_int);
    event_free (evfifo);
    close(socket);
    unlink(fifo);
    return (0);
}

