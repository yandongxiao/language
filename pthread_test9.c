#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <string.h> /* for strsignal */

void
test_sigwait(void)
{
    sigset_t newset, oldset;

    /* normally, use the newset as the parameter of pthread_sigmask and sigwait. */
    /* If the SIGINT or SIGQUIT happen, signal will be blocked. */
    sigemptyset (&newset);
    sigaddset (&newset, SIGINT);
    sigaddset (&newset, SIGQUIT);
    pthread_sigmask (SIG_SETMASK, &newset, &oldset);
    

    /* Note: when signal in the newset signal happens, signal handler will not be execute.
        * And, when sigwait returns, the @signo will be removed from pending set.
        *
        * When other signal happens, execute the signal handler. when done, go to wait.
        */
    int signo;
    sigemptyset (&newset);
    sigaddset (&newset, SIGINT);
    /*
        * SIGINT and SIGQUIT will be blocked, because pthread_sigmask called.
        * until you send SIGINT, then return.
        * SIGINT has been remove from pending signal set. 
        * When reset the signal set, SIGQUIT happended.
        */
    sigwait (&newset, &signo);
    printf ("sigwait waitting for signal : %s\n", strsignal(signo));
    pthread_sigmask (SIG_SETMASK, &oldset, NULL);
}

void
test_sigsuspend(void)
{
    sigset_t newset;

    sigemptyset (&newset);
    sigaddset (&newset, SIGINT);
    pthread_sigmask (SIG_SETMASK, &newset, NULL);


    /*
        * 1. sigsuspend use SIG_SETMASK manner, assign new signals to block.
        * 2. the blocked signal will be pending state. (do not remove it)
        * 3. when other signal happens, and signal handler will be executed. then sigsuspend will
        *     return. But note, before return, when the blocked signal unblocked, thread will execute
        *     the signal handler.
        */
    sigemptyset (&newset);
    sigaddset (&newset, SIGQUIT);
    int cc = sigsuspend (&newset);
    printf ("sigsuspend return %d\n", cc);
}

void
sig_int (int signo)
{
    printf ("enter sig_int\n");
}

int main (void)
{
    signal (SIGINT, sig_int);
//    test_sigwait();
    test_sigsuspend();
    return 0;
}
