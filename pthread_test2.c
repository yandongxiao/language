#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  * the main thread terminated earlier.
  *
  * the returned value of process is 0
  * in main thread, return 0 <==> exit(0)
  * it is indeterminate which thread-the caller or the new thread will next execute.
  *
  * Note:
  *    the new thread use the same standard IO buffer. the print out may be
  *    "leave parrent\n"    
  *    "enter child\n"
  *    "enter child\n"
  *    the root cause is that: two thread share the memmory, should sync.
  */

void*
thread_cb (void *arg)
{
    printf ("enter child\n");
    sleep (100);
    printf ("leave child\n");
    return NULL;
}

int main (void)
{
    pthread_t tid;
    pthread_create (&tid, NULL, thread_cb, NULL);
    
    printf ("leave parrent\n");
    return 0;
}

