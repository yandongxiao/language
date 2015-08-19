#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

/*
  *
  * sigwait will only clear the pending state of SIGINT.
  * when reset the signal mask, SIGQUIT handle happens.
  *
  */

int main (void)
{
    sigset_t newmask;
    sigemptyset (&newmask);
    sigaddset (&newmask, SIGINT);
    sigaddset (&newmask, SIGQUIT);
    
    sigprocmask (SIG_BLOCK, &newmask, NULL);
    sleep (5);

    int signo;
    sigwait (&newmask, &signo);
    printf ("the waited signal is <%s>\n", strsignal(signo));

    sigset_t pendingset;
    sigpending (&pendingset);
    if (sigismember (&pendingset, SIGINT))
        printf ("signal SIGINT has not been cleared");
    if (sigismember (&pendingset, SIGQUIT))
        printf ("signal SIGQUIT has not been cleared");

    sigprocmask (SIG_UNBLOCK, &newmask, NULL);
    return 0;
}
