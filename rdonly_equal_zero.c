#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main ()
{
    printf ("%d\n", O_RDONLY);    
    printf ("%d\n", O_WRONLY);    
    return 0;
}
