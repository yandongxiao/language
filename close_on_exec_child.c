#include <unistd.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    /* get the file descripto from parrent. */
    int fd = atoi (argv[1]);
    const char *str = "I am a child\n";
    ssize_t len = write (fd, str, strlen(str));
    if (len == -1) {
        perror ("child write failed");
        return -1;
    }

    return 0;
}
