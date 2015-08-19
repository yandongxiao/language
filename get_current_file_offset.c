#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int 
main (void)
{
    int fd = open ("/tmp/aaa", O_RDONLY | O_APPEND);

    char buf [512];
    ssize_t len;
    while ((len = read(fd, buf, sizeof (buf))) > 0) {
        write (STDOUT_FILENO, buf, len);
    }

    off_t offset = lseek (fd, 0, SEEK_CUR);

    printf ("%d\n", (int)offset);
    return 0;
}
