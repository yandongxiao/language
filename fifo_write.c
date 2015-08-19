#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define FIFO "/tmp/myfifo"

int
main (void)
{
    printf ("original mode is %o\n", umask (0));
    /* note: the second flag format. */
    /* failed when mkfifo on mounted fs, same with mkfifo command.*/
    int fd = mkfifo (FIFO, 0777);
    if (fd != 0 && errno != 17) {
        perror ("mkfifo failed");
        printf ("%d\n", errno);
    }

    /* same with fifo_read, if you do not use O_NONBLOCK, open will be block*/
    /* If there is no process that calls open to the read end of pipe, it will retuen -1. */
    printf("Preparing for reading bytes...\n");  
    int wfd = open (FIFO, O_WRONLY | O_NONBLOCK);
    if (wfd == -1) {
        perror ("open for write failed");   
    }
    write (wfd, "helloworld", 10);
    close (wfd);
    return 0;
}
