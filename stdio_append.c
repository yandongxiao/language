
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void
test_stdio (void) {
    FILE *stream = fopen ("/dev/fd/1", "a");
    fwrite ("helloworld\n", 1, 11, stream);
    fclose (stream);
  
    freopen ("/dev/fd/1", "a", stdout);    
    printf ("hello\n");
    
    pid_t pid = fork ();

    if (0 == pid) {
        printf ("I am a child\n");
    }
    else if (pid > 0) {
        sleep (1);
        printf ("world\n");
    }
}

int
main (int argc, char **argv)
{
    test_stdio();
    return 0;
}
