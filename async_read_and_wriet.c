#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/*
 *  read_pipe : confirmed
 *
 *     when you want to read data from children's stdout. First create a pipe, secondly call dup2(fd[1], STDOUT_FILENO).
 *     If O_NONBLOCK is unset, read will waiting for reading until child process exit (file descripter will close).
 *     If O_NONBLOCK is unset. Before children exit, it write some data; then parent process can read out the data.
 *     when O_NONBLOCK is set, read will return immedidately. You'd better check whether the errno equals EWOULDBLOCK or EAGAIN.
 */
int
read_pipe(int argc, char **argv)
{
    int fd[2];
    int pid;
    int ret;
    char buf[1024];

    /* create a pipe. */
    if(argc == 2)
        pipe2(fd, O_NONBLOCK);
    else
        pipe2(fd, 0);

    if((pid=fork()) == 0) {     /* child process. */
        close(fd[0]);
        sleep(2);
        write(fd[1], "nihao", 5);
        close(fd[1]);
        return 0;        /* NOTE: must return. */
    }else if(pid<0){
        perror("fock error");
    }

    close(fd[1]);
    ret = read(fd[0], buf, 1024);
    if(ret < 0) {
        if(EAGAIN == errno || O_NONBLOCK == errno)
            printf("nonblock error: resource is not ready");
        else
            perror("read error");
    }else{
        buf[ret] = '\0';
        printf("len=%d, contents=%s", ret, buf);
    }

    close(fd[0]);
    return 0;
}

int 
main(int argc, char **argv) {
    read_pipe(argc, argv);
}

