#include <stdio.h>
#include <unistd.h>

int main ()
{
    int i;
    for (i=0; i<1000; i++) {
        printf ("hello\n");
        sleep (1);
    }

}
