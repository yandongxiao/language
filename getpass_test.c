#include <unistd.h>
#include <stdio.h>

int main (void)
{
    char *pass = getpass ("password:");
    printf("you input %s\n", pass);
    return 0;
}
