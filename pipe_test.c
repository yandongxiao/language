#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void
sigpipe(int signo)
{
    printf ("SIGPIPE happend\n");
}

int main (void)
{
    int pipefd[2];
    pipe (pipefd);
    close (pipefd[0]);

    signal (SIGPIPE, sigpipe);
    write (pipefd[1], "nihao", 6);
    printf ("done\n");
    return 0;
}
