#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
  * when detached thread terminate, resource will be released auto.
  * you can not, and it is impossible to get detached threads exit status.
  */

void*
thread_cb (void *arg)
{
    /*
        * event you are detached thread, main thread return, call exit
        * new thread will be terminated too.
        */
    sleep (20);
    printf ("child done\n");
    exit(0);
}

int main (void)
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_create (&tid, &attr, thread_cb, NULL);
    pthread_join (tid, NULL);
    pthread_attr_destroy (&attr);
    sleep (10);
    printf ("parrent done\n");

    /* there is memory leak,
        * event child thread call exit(0)(return dose not work)
        */
    pthread_exit(NULL);
}


