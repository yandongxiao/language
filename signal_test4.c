#include <unistd.h> /* for sleep */
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/signal.h>

/* 
 * when handle SIGINT, new signal SIGINT will be blocked until @func done.
 * and then, @func will handle the block sigint signal again.
 *
 * Note: Only block one sigint signal, other SIGINT will be droped.
 */
void
sig_int (int sig)
{
    printf ("enter sig_int\n");
    sleep (3);
    printf ("leave sig_int\n");
}

int
main (void)
{
    signal (SIGINT, sig_int);
    sleep (10);
    printf ("done\n");
    return 0;
}
