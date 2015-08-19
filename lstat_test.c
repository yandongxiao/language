#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
    struct stat buff;
    int cc = lstat (argv[1], &buff);
    assert (cc == 0);

    printf ("blocksize = %d\n", (int)buff.st_blksize);
    printf ("blocksize = %d\n", (int)buff.st_blocks);
    printf ("size = %d\n", (int)buff.st_size);
    printf ("uid = %d\n", (int)buff.st_uid);
    printf ("gid = %d\n", (int)buff.st_gid);
    printf ("nlink = %d\n", (int)buff.st_nlink);
    printf ("mode = %o\n", (int)buff.st_mode);
    
    if (S_ISREG(buff.st_mode)) {
        printf ("regular file\n");
    }

    printf ("%o\n", buff.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    return 0;
}

