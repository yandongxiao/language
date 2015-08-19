#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/resource.h>

void
daemonize (const char *cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    /* step 1 : clear the file mask */
    umask (0);
    
    /* step 2 : get the max value of fd */
    getrlimit (RLIMIT_NOFILE, &r1);

    /* step 3 : become a session leader. */
    pid = fork ();
    if (pid != 0)
        exit (-1);
    setsid ();

    /*  */

}
