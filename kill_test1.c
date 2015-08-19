#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main ()
{
    pid_t pid = fork();
    if (pid == 0) {
        char *params [] = {"func", NULL};
        pid_t pid = getpid ();
        setpgid (pid, pid);
        execvp ("/home/ubuntu-32/share/developing/4_0_working/base/example/bin/ttest", params);
    }

    kill (0-pid, SIGINT);

    return 0;
}
