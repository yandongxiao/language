#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

 /*
    *  every login shell and windows shell(include ctr+shift+t created shell)
    *  will create a new session.
    *  
    *  every time you fork/exec a childprocess(include bash) from shell, shell
    *  will create a new process group. 
    *
    *  the child will inherits the session id of parrent.
    */

int main (void)
{
    int fd;
    fd = open ("/dev/tty", O_RDONLY);
    if (fd == -1)
        printf ("do not have control terminal\n");
    else
        printf ("have control terminal\n");            
    close (fd);
    
    /* the are in the same session. */
    printf ("session test:\n");
    printf ("    the process id of bash is : %d\n", getppid());
    printf ("    the session id of bash is : %d\n", getsid (getppid ()));
    printf ("    the session id of me is : %d\n", getsid (getpid ()));

    /* the are not in the same session, but they both the leader of their own process group */
    printf ("pgroup test:\n");
    printf ("    the process group id of bash is: %d\n", getpgid (getppid()));
    printf ("    the process id of bash is : %d\n", getppid());

    printf ("    the process group id of me is  : %d\n", getpgrp ());
    printf ("    the process id of bash is : %d\n", getpid());
    
    if (fork()==0) {
        printf ("child process : \n");
        printf ("    the process id of child is : %d\n", getpid());        
        printf ("    the process group id of child is  : %d\n", getpgrp ());
        printf ("    the session id of child is : %d\n", getsid (0));
        
        pid_t session = setsid();
        if (session == -1)
            perror ("setsid failed");
        printf ("after setsid\n");
        printf ("    the process group id of child is  : %d\n", getpgrp ());
        printf ("    the session id of child is : %d\n", getsid (0));
        /* have no effect to process group and session id. */
//        execl ("./bin/getsid", NULL);
        if (open ("/dev/tty", O_RDONLY) == -1)
            printf ("new sid do not have control terminal\n");
        else
            printf ("new sid have control terminal\n");            
        printf ("error\n");
        sleep(1000);
        return 0;
    }

    sleep (10000);
    return 0;
}
