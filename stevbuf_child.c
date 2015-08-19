#include <stdio.h>
#include <unistd.h>

int main ()
{
    char buff[512];
    //setvbuf (stdin, NULL, _IONBF, 0);
    //scanf ("%s", buff);
    //int cc = read (STDIN_FILENO, buff, 512);
    //buff[cc]='\0';
    fgets (buff, 512, stdin);
    printf ("child recvive : %s\n", buff);
    sleep (120);
    return 0;
}
