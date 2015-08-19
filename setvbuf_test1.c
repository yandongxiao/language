#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
    pid_t pid;
    int pipefd[2];

    pipe(pipefd);
    pid = fork ();

    if (pid == 0) {
        dup2 (pipefd[0], STDIN_FILENO);
        char buff[512];
        int cc = read (STDIN_FILENO, buff, 512);
        buff[cc] = '\0';
        fprintf (stderr, "%s\n", buff);
        return 0;
    }

    int cc = write (pipefd[1], "helloworld", 10);
    assert (cc > 0);
    return 0;
}

