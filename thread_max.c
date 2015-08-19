#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

void*
func(void *arg)
{
    sleep (1000000);
    return NULL;
}

int main ()
{
    /* setrlimit, but has no effect */
    struct rlimit limit;
    limit.rlim_cur = limit.rlim_max = 1000;
    setrlimit (RLIMIT_NPROC, &limit);

    int num = 1;
    while (1) {
        pthread_t thread;
        int cc = pthread_create(&thread, NULL, func,NULL);	/* default 383 */
        if (cc || num>10000) {
            printf (" one process has <%d> threads\n", num);
            break;
        }
        num++;
    }

}
