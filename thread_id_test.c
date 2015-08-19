#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void*
thread_cb (void* arg)
{
    printf ("child thread is %u\n", pthread_self() );
    pause ();
    return NULL;
}

int main ()
{
    pthread_t tid;
    pthread_create (&tid, NULL, thread_cb, NULL);

    pause ();
    return 0;
}
