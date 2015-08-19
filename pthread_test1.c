#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
  * get the returned value from child thread.
  * 
  * like waitpid, call pthread_join to release some resource back to system
  *
  * If multiple threads simultaneously try to join with the same thread, 
  * the result is undefined.
  * NOTE: EINVAL, another thread is already waiting to join this thread.
  *        EDEADLK, a deadlock was detected. or thread is it the calling thread.
  * you have pthread_equal, so do not use == to compare.
  */

void*
thread_cb (void *arg)
{
    int *pa  = malloc (sizeof(int));
    *pa = 10;

    /* not returned to parent thread, any thread can get it. */
    return (void*)pa;
}

int main (void)
{
    pthread_t tid;
    void *retval;
    
    pthread_create (&tid, NULL, thread_cb, NULL);

    /* any other thread in process, can call it. Ont only parrent.
        * all of the threads in a process are peers: any thread can join with
        * any other in the process.
        * or will have a "zombie thead"
        */
    pthread_join (tid, &retval);

    printf ("the child thread return %d\n", *(int*)retval);
    free(retval);
    
    return 0;
}

