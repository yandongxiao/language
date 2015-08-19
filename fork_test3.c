#include <unistd.h>     /* fork */
#include <stdio.h>
#include <stdlib.h>

static int s_var = 66;
#define child_str   "this is child\n"
#define parrent_str "this is parrent\n"
static const char *filename = "/tmp/mytestfile";

void
call_vfork ()
{
    int num = 8;
    pid_t pid;

    if ((pid=vfork()) == 0) {
        s_var++;
        num++;
        /* If you think you can write return, you are wrong. program will always run. */
        /* exit do not close stdout stream, you can use printf at parrent. IN LINUX. */
        printf ("child: s_var=%d, num=%d\n", s_var, num);
        return;
    }
    exit(0);
}

int main ()
{   
    int a;
    call_vfork();
    a++;
    printf ("a==%d\n", 0);
    return 0;
}


