#include <unistd.h> /* for fork*/
#include <fcntl.h>
#include <stdlib.h> /* for exit */
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
 * you can use the file descriptor at fork.
 * but not on exec
 */
int 
test (int fd)
{
    /* set close on exec */
    int cc = fcntl (fd, F_SETFD, FD_CLOEXEC);
    if (cc == -1) {
        perror ("fcntl failed");
        exit (-1);
    }

    pid_t pid = fork();
    if (pid==0) {
        const char *str = "you can write when fork\n";
        ssize_t cc = write (fd, str, strlen(str));
        assert (cc != -1);
        
        /* you must pass file descriptor by string. */
        /* note how you pass a file descriptor to child process. */
        char buff[64];
        sprintf (buff, "%d", fd);
        execl ("child", "child", buff, NULL); 
        assert (1==0);
    }
    else if (pid > 0) {
        write (fd, "parrent\n", 8);
    }
    
    return 0;
}

int main (void)
{
    test (STDOUT_FILENO);

    int fd = open ("/tmp/aaa", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror ("open failed");
        exit (-1);
    }
    test (fd);
}
