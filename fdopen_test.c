#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* failed */

FILE*
temp_file_create (const char *filepath)
{
    int fd = open (filepath, O_CREAT | O_RDWR, 0777);
    if (fd == -1)
        return NULL;

    /* pass "rw" will cause wierd failure when you call fprintf
        * "w+" for reading and writing 
        */
    FILE *file = fdopen (fd, "w+");
    int cc = unlink (filepath);
    if (cc != 0) {
        perror ("ulink error");
    }
    /* the fdopen has close the file descriptor fd. 
        * the more worse is : the closed fd will be reused by the FILE*.
        * you close fd, will make me never wirte to the file.
        */
//    close (fd);
    return file;
}

int 
main (void)
{
    FILE *file = temp_file_create (".test");
    if (NULL == file)
        perror ("create failed");

    int len = fprintf (file, "nihao");
    if (len == -1)
        perror ("fprintf failed");
    if (fflush (file) == EOF) {
        perror ("fflush failed");
    }
    fclose (file);
    return 0;
}
