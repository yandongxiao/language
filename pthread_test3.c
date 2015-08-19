#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
  * the new thread inherits a copy of the creating thread's signal mask.
  * the set of pending signals for the new thread is empty.
  */

void*
thread_cb (void *arg)
{
    sigset_t oldmask;
    pthread_sigmask (SIG_SETMASK, NULL, &oldmask);

    if (sigismember(&oldmask, SIGINT))
        printf ("the child thread signal mask : %d\n", oldmask);

    return NULL;
}

int main (void)
{
    pthread_t tid;

    sigset_t newmask, oldmask;
    sigemptyset (&newmask);
    sigaddset (&newmask, SIGINT);
    pthread_sigmask (SIG_SETMASK, &newmask, &oldmask);
    
    pthread_create (&tid, NULL, thread_cb, NULL);
    pthread_join (tid, NULL);

    return 0;
}


