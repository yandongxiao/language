#include <unistd.h> /* fork */
#include <stdio.h>

static int s_var = 66;
#define child_str   "this is child\n"
#define parrent_str "this is parrent\n"
static const char *filename = "/tmp/mytestfile";

int main ()
{
    int num = 8;
    FILE *file = fopen (filename, "w");
    pid_t pid;

#if 1
    /* add this the file will be parrent, child. */
    /* call it before any write operation. */
    setvbuf (file, NULL,_IOLBF, 0);
#endif
    
    /* this line will be printed when exit. */
    /* content is parent, child, parrent. */
    fprintf (file, parrent_str);
    if ((pid=fork()) == 0) {
        /* The buffer has been stored  @parrent_str when fork. */
        /* so the child will print two line first */
        fprintf (file, child_str);
        s_var++;
        num++;
        printf ("child: s_var=%d, num=%d\n", s_var, num);
    }
    else if (pid > 0) {
        sleep (2);
        printf ("parent: s_var=%d, num=%d\n", s_var, num);
        wait (NULL);
    }

    return 0;
}
