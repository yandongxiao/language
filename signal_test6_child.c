#include <signal.h>
#include <unistd.h>
#include <stdio.h>


/*
  * 1. The signal mask will be inherited by me.
  *
  * 2. the struct sigaction has a @sa_mask, It will be set 0 in child process.
  * 3. If the SIGINT signal is set SIG_DFL or SIG_IGN, it will be inherited, 
  *     set sig handler will be reset to SIG_DFL.
  */
 
int
main (void)
{
    sigset_t oldmask;
    sigprocmask (SIG_UNBLOCK, NULL, &oldmask);

    /* do not do this in programming. */
    printf ("child mask is 0x%x\n", (int)oldmask.__val[0]);

    struct sigaction oldact;
    sigaction(SIGINT, NULL, &oldact);
    printf ("child SIGINT mask is 0x%x\n", (int)oldact.sa_mask.__val[0]);
    printf ("child SIGINT handler is 0x%p\n", oldact.sa_handler);

    return 0;
}


