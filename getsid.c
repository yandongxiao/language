#include <unistd.h>

int main (void) {

    printf ("after execl, the session id is : %d\n", getsid(0));
    printf ("after execl, the process group id is : %d\n", getpgrp());

}
