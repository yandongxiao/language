#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/signal.h>

/*
 * set sigal action 
 *
 * struct sigaction actions;
 *
 * memset(&actions, 0, sizeof(actions));
 * sigemptyset(&actions.sa_mask);
 * actions.sa_flags = 0;
 * actions.sa_handler = sighand;
 * rc = sigaction(SIGALRM, &actions, NULL);
 * 
 * normally, one sigaction object has one signal handler, and handle one signal.
 *
 * Note: the sigaction can affect his children.
 */

 /*
   * every thread has a signal set concept.
   * you can decide whether accept signal. default you accept all signal.
   *
   * call sigfillset(&mask), you can ignore all signal.
   */

/*
  * you can use pthread_kill to send signal between threads in a process.
  * 
  * the hung thread will become active.
  */

#define NUMTHREADS 3
void sighand(int signo);
 
void *threadfunc(void *parm)
{
    pthread_t tid = pthread_self();
    int rc;
 
    printf("Thread %lu entered\n", tid);
    rc = sleep(30);
    printf("Thread %lu did not get expected results! rc=%d\n", tid, rc);
    return NULL;
}
 
void *threadmasked(void *parm)
{
    pthread_t tid = pthread_self();
    sigset_t mask;
    int rc;

    printf("Masked thread %lu entered\n", tid);
 
    sigfillset(&mask);
    rc = pthread_sigmask(SIG_BLOCK, &mask, NULL);
    if (rc != 0)
    {
        printf("%d, %s\n", rc, strerror(rc));
        return NULL;
    }
 
    rc = sleep(15);
    if (rc != 0)
    {
        printf("Masked thread %lu did not get expected results! "
                       "rc=%d \n", tid, rc);
        return NULL;
    }
    printf("Masked thread %lu completed masked work\n", tid);
    return NULL;
}
 
int main(int argc, char **argv)
{
    int rc;
    int i;
    struct sigaction actions;
    pthread_t threads[NUMTHREADS];
    pthread_t maskedthreads[NUMTHREADS];
 
    printf("Enter Test case - %s\n", argv[0]);
 
    printf("Set up the alarm handler for the process\n");
    memset(&actions, 0, sizeof(actions));
    sigemptyset(&actions.sa_mask);
    actions.sa_flags = 0;
    actions.sa_handler = sighand;
 
    rc = sigaction(SIGALRM, &actions, NULL);
 
    printf("Create masked and unmasked threads\n");
    for(i=0; i<NUMTHREADS; ++i)
    {
        rc = pthread_create(&threads[i], NULL, threadfunc, NULL);
        if (rc != 0)
        {
            printf("%d, %s\n", rc, strerror(rc));
            return -1;
        }
 
        rc = pthread_create(&maskedthreads[i], NULL, threadmasked, NULL);
        if (rc != 0)
        {
            printf("%d, %s\n", rc, strerror(rc));
            return -1;
        }
    }
 
    sleep(3);
    printf("Send a signal to masked and unmasked threads\n");
    for(i=0; i<NUMTHREADS; ++i)
    {
        rc = pthread_kill(threads[i], SIGALRM);
        rc = pthread_kill(maskedthreads[i], SIGALRM);
    }
 
    printf("Wait for masked and unmasked threads to complete\n");
    for(i=0; i<NUMTHREADS; ++i) {
        rc = pthread_join(threads[i], NULL);
        rc = pthread_join(maskedthreads[i], NULL);
    }
    printf("Main completed\n");
    return 0;
}
 
void sighand(int signo)
{
    pthread_t tid = pthread_self();
    printf("Thread %lu in signal handler\n", tid);
    return;
}
