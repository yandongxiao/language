#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* child can not receive helloworld */

int main ()
{
    pid_t pid;
    int pipefd[2];

    pipe(pipefd);
    pid = fork ();

    if (pid == 0) {
        dup2 (pipefd[0], STDIN_FILENO);
        int cc = execlp ("./child", "child", NULL);
        assert (1==2);
        return 1;
    }
    
    /* redirecvt stdout, child use fgets. It will not work. */
    //dup2 (pipefd[1], STDOUT_FILENO);
    //printf ("helloworld");
    //fflush (NULL);
    int cc = write (pipefd[1], "helloworld", 10);
    assert (cc > 0);
    sleep (100);  /* for send SIGTERM both. */
    return 0;
}

