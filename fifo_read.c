#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define FIFO "/tmp/myfifo"

int main (void)
{
    /* If you do not use O_NONBLOCK flag, open will be blocked 
     * until the write fifo is opened.
     */
    int rfd=open(FIFO, O_RDONLY | O_NONBLOCK);  
    if(rfd==-1)  
    {  
        perror("open!\n");  
        return -1;
    }

    char buff [1024];
    int len = 0;
    while (1) {
        len = read (rfd, buff, 1024);
        if ((len == -1 && (errno == EAGAIN || errno == EWOULDBLOCK) )
                || len == 0) {
            printf ("len=%d\n", len);
            sleep (3);
            continue;
        }
        if (len == -1) {
            perror ("read error");
            printf ("error=%d\n", errno);
            // Resource temporarily unavailable
            return -1;
        }
        break;
    }

    buff[len] = '\0';
    printf ("%s\n", buff);

    return 0;
}

