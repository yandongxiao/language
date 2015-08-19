#include <unistd.h>
#include <stdio.h>

int main ()
{
    char buff[1024];

    printf ("login user name is <%s>\n", getlogin());
//    printf ("cuserid user name is <%s>\n", cuserid(buff));

    return 0;
}
