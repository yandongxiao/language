#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/signal.h>

int i = 0;

/*
 * create a signal itself.
 *
 * 1/0 will cause the SIGFPE signal.
 * so, after the signal has been handled. 
 * try to execute the command again.
 */

void
func (int sig)
{
    i = 1;
    printf ("error sigfpe\n");
}

int
main (void)
{
    int a;
    signal (SIGFPE, func);

    /* execute 1/0, even i has been changed to 1.*/
    a = 1/i;    
    printf ("done\n");
    return 0;
}
