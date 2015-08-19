#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void*
thread_cb (void *arg)
{
    int type;
    int stat;

    /* both default value is zero. */
    /*
        * PTHREAD_CANCEL_ENABLE == 0
        * PTHREAD_CANCEL_DEFERRED == 0  //ÍÆ³Ù
        * PTHREAD_CANCELED == (void*)-1
        */
    pthread_setcanceltype (0, &type);
    pthread_setcancelstate(0, &stat);

    return NULL;
}

int main (void)
{
    pthread_t tid;
    pthread_create (&tid, NULL, thread_cb, NULL);
    pthread_join(tid, NULL);
    return 0;
}

