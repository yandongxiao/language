#include <unistd.h>     /* fork */
#include <stdio.h>
#include <stdlib.h>

static int s_var = 66;
#define child_str   "this is child\n"
#define parrent_str "this is parrent\n"
static const char *filename = "/tmp/mytestfile";

int main ()
{
    int num = 8;
    pid_t pid;

    printf ("before vfork\n");
    if ((pid=vfork()) == 0) {
        s_var++;
        num++;
        /* If you think you can write return, you are wrong. program will always run. */
        /* exit do not close stdout stream, you can use printf at parrent. IN LINUX. */
        fclose (stdout);
        exit(0);
    }
    else if (pid > 0) {
        sleep (2);
        printf ("parent: s_var=%d, num=%d\n", s_var, num);
        wait (NULL);
    }

    return 0;
}

