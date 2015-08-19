#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/signal.h>
#include <unistd.h>  /* for sleep */
/* 
 * when enter sig_int but before leave, there is another signal sig_tstp,
 * 
 * the thread will stop sig_int handle and handle sig_tstp. then sig_tstp done,
 * go on handling sig_int.
 */
void
sig_int (int sig)
{
    printf ("enter sig_int\n");
    sleep (3);
    printf ("leave sig_int\n");
}

void
sig_tstp (int sig) 
{
    printf ("enter sig_tstp\n");
    sleep (3);
    printf ("leave sig_tstp\n");
}

int
main (void)
{
    signal (SIGINT, sig_int);
    signal (SIGTSTP, sig_tstp);

    sleep (10);
    printf ("done\n");
    return 0;
}
