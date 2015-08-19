#include <unistd.h>
#include <stdio.h>
#include <sys/signal.h>
#include <pthread.h>

/*
 * at this time, we send a SIGINT from terminal.
 *
 * we found that: the main thread will be waked up, and handle the signal.
 *
 * If the main thread block the signal, send the signal the thread which is 
 * the first one that handle the signal.  no matter how many signals sent to it,
 * it is the thread business, not others.
 *
 * If the thread terminate, find the second.
 *
 * The order of thread is based on the time thread startup.
 * 
 */

void sighand(int signo)
{
    pthread_t tid = pthread_self();
    printf("Thread %lu in signal handler\n", tid);
    return;
}

void * 
newfunc (void *data)
{
    struct sigaction action;
    sigemptyset (&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = sighand;
    sigaction (SIGINT, &action, NULL);

    printf ("enter %s, tid is %lu\n", __func__, pthread_self());

    sigset_t mask;
    sigemptyset (&mask);
    sigaddset (&mask, SIGINT);

    pthread_sigmask (SIG_UNBLOCK, &mask, NULL);

    sleep (100);
    sleep (100);

    printf ("leave %s\n", __func__);
    return NULL;
}

int 
main (void)
{
  /* if you uncomment it, the newfunc thread will handle the siganl. */

    sigset_t mask;
    sigfillset (&mask);
    pthread_sigmask (SIG_BLOCK, &mask, NULL);

    pthread_t thread1;
    pthread_create (&thread1, NULL, newfunc, NULL);

    pthread_t thread2;
    pthread_create (&thread2, NULL, newfunc, NULL);

//    sleep (100);
    
    pthread_join (thread1, NULL);
    pthread_join (thread2, NULL);
    return 0;
}
