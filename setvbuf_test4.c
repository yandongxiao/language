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
        dup2 (pipefd[1], STDOUT_FILENO);
        int cc = execlp ("./child", "child", NULL);
        assert (1==2);
        return 1;
    }

    char buff[512];
//    int n = read (pipefd[0], buff, 512);
//    buff[n] = '\0';
    FILE *f = fdopen (pipefd[0], "r");
    fgets (buff, 512, f);
    printf ("parrent buff==<%s>", buff);
    sleep (100);  /* for send SIGTERM both. */
    return 0;
}

