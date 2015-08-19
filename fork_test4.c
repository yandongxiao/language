#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main ()
{
    /* man tell me : the DIR defined in dirstream.h of the glibc */
    DIR *dir = opendir ("/tmp");
    int fd = *(int*)(dir);
    int flag = fcntl (fd, F_GETFD, 0);
    
    printf ("dir close on exec flag os : %d\n", flag);
    return 0;
}
