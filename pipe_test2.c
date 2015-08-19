#include <stdio.h>


int main ()
{
    int fds[2];
    
    pipe (fds);

    if (fork()==0) {
        char c;
        read (fds[0], &c, 1);
        sleep (1);
        read (fds[0], &c, 1);
        printf ("child done\n");
        return 0;
    }

    write (fds[1], "he", 2);

    /* pipe will not be stopped, event there are data in pipe */
    write (fds[1], "wo", 2);
    printf ("parrent done\n");
}
