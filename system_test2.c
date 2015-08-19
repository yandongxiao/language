#include <stdlib.h> /* for system */
#include <stdio.h>

void
pr_exit (int status) 
{
    if (WIFEXITED(status)) {
        printf ("normal termination, exit status = %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        printf ("abnormal termination, signal number=%d\n", WTERMSIG(status));
    }
    else {
        printf ("other status of child\n");
    }
}


void
test1 (void)
{
    /* not all system support system */
    /* system (NULL) return non 0 means that the system support this function */
    printf ("system(NULL) == %d\n", system(NULL));
}

void
test2 (void)
{
    /* system return the process exit status, but you should not check it like this. */
//    printf ("system(aaa) == %d\n", system("aaa"));

    /* normal termination, exit status = 127. */
    int cc = system("aaa");
    if (cc < 0) {
        perror ("system failed");
    }
    pr_exit (cc);
}

int
main ()
{
    test1 ();
    test2 ();
    return 0;
}
