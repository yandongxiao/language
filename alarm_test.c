#include <unistd.h>
#include <stdio.h>

int
test1 (void)
{
    /* we get the return value 142 */
    alarm (1);
    sleep (1000);
    return -1;
}

int
test2 (void)
{
    pid_t pid;
    if ((pid=fork())==0) {
        alarm (1);
        sleep (1000);
    }
    else if (pid>0) {
        /* the returned status is 14 */
    }

}

int main ()
{
    alarm (0);
    sleep (10);
    return 0;
}
