#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*
  * system do the following thing:
  *
  * fork its child process <sh> ( normally, sh is supported on all system )
  * see argu_print.sh for more information about run a executable file.  
  * 
  * then, system will call <waitpid> to wait <sh> terminate.
  *
  * So, normally fork, exec, waitpid will be called successfully. 
  *
  */


/* the process relation:
  * a.out -->sh-->sleep
  * note: not bash.
  * pstree
  */
void test1()
{
    system("sleep 1000");
}

/* interpreter file, the process relation:
  *  a.out -->sh-->test-->sleep
  *
  * comment the first line
  * a.out -->sh-->sh-->sleep
  */
void test2()
{
    if (system ("/tmp/test"))
        strerror(errno);
}

int
main (void)
{
    test2();
    return 0;
}
