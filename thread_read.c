#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void
sigint (int signo)
{
    printf ("sigint, thread %d\n", pthread_self());
    sleep (3);
    exit (0);
}

void*
thread_func (void *arg)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);

    printf ("thread %d\n", pthread_self());
    sleep (10000);
    return NULL;
}

int main ()
{
    int n;
    char buff[124];

    signal (SIGINT, sigint);
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pthread_t td;
    pthread_create (&td, NULL, thread_func, NULL);

    n = read (0, buff, 1024);   /* read do not return back */
    printf ("n == %d\n", n);
    return 0;

}
