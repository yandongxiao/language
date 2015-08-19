#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

void test1 ()
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        execl ("./bin/argu_print", 
                    "argu_print", 
                    "argu1", 
                    "argu2",
                    NULL);
        assert (1==2);
    }
    else if (pid>0) {
        wait (NULL);
    }

}

void test2 ()
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        execl ("./bin/../argu_print.sh",    /* the argv[0]*/
                    "argu_print",   /* ignore */
                    "argu1",    /* after the interpreter argument */
                    "argu2",
                    NULL);
        assert (1==2);
    }
    else if (pid>0) {
        wait (NULL);
    }


}

int main ()
{
    test1 ();
    test2 ();

    return 0;
}
