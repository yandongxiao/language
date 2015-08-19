#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
    pid_t pid;
    int pipefd[2];

    pipe(pipefd);
    pid = fork ();

    if (pid == 0) {
        dup2 (pipefd[0], STDIN_FILENO);
        char buff[512];
#if 0 
/* select do not work */
	FILE *fp = fdopen (STDIN_FILENO, "r");
	int fd = fileno(fp);
	fd_set set;
	FD_ZERO (&set);
	FD_SET (fd, &set);
	select (fd+1, &set, NULL, NULL, NULL);
	printf ("get somethinf\n");
#endif
        fgets(buff, 512, stdin);
        fprintf (stderr, "%s\n", buff);
        return 0;
    }
    
    int cc = write (pipefd[1], "helloworld", 10);
    assert (cc > 0);
    sleep (10);  /* for send SIGTERM both. */
    return 0;
}

