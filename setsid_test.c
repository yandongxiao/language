#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main ()
{
    /* the leader of process group can not call setsid. */
    pid_t pid = fork();
    if (pid > 0)
        exit(0);

    int cc = setsid ();
    pid = fork ();
    if (pid == 0) {
        /* If it is SIGSTOP, chhild will not be killed by SIGHUP.
             *  that is to say: only when SIGTSTP, child will get SIGHUP signal.
             */
//        raise (SIGTSTP);

        /* can not get SIGHUP */
        pause ();
    }

    sleep (10);
    exit(0);
    return 0;
}
