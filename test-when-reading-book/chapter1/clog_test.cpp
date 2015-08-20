#include <iostream>

/* 1. there is no cunistd.h */
#include <unistd.h>     /* needed by STDOUT_FILENO */
#include <fcntl.h>

using namespace std;

void where_print_test ()
{
    /* 2. there is no cout.close() method, same with cin cerr clog */
    close (STDERR_FILENO);

    /* 3. If close stderr_fileno, no message printed. */
    /* 4. clog badbit will be set, but cerr not set */
    clog << "clog message" << endl;
    if(clog.bad()) {
        cout << "clog badbit set" <<endl;
    }

    int fd = open ("/dev/fd/2", O_WRONLY);
    if (fd != STDERR_FILENO) {
        dup2 (fd, STDERR_FILENO);
        close (fd);
    }

    /* 5. we can not write using cerr too. */
    if (cerr) {
        /* entered but not printed */
        cerr << "cerr message" <<endl;
    }
    
}

void howto_redirect ()
{
    /* 1. redirect stdout and stderr */
    int fd = open ("abc", O_WRONLY | O_CREAT);
    if (fd != STDERR_FILENO) {
        dup2 (fd, STDERR_FILENO);
        close (fd);
    }
    clog << "clog redirect" << endl;  /*no buffered*/
    
    /* 2. the following cout will be printed in @abc */
    cout << "before redirect";
    /* 3. If you use cerr, cout will be flushed */
    cerr << "use clog flush cout" << endl;
    dup2 (STDERR_FILENO, STDOUT_FILENO);

    /* 3. event redirected to file, cout is still line buffered.
     * different from printf
     */
    cout << "cout redirect\n";
    sleep(1000);
}

void howto_print_test ()
{
    /* 1. sleep is the only way, we can find */
    /* 2. clog,cerr are not buffered, cout line buffered */
    cout << "cout\n";
    sleep (1);
    cerr << "cerr";
    sleep (1);
    clog << "clog";
    sleep (1);

    /* clog, cout, cerr share the same file, the printed order
     * is alwayse first, second, third. */
    cout << "first";   
    sleep (3);
    /* 3. cout, cerr and cin are related, see p182
     * Note, not include clog
     */
    cerr << "second";
}

int main ()
{
    howto_print_test();

    howto_redirect ();

    where_print_test();

    return 0;
}
