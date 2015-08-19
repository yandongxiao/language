#include <stdio.h>  /* for printf */
#include <fcntl.h>  /* for open */
#include <assert.h> /* for assert */
#include <unistd.h> /* for write */
#include <string.h> /* for strlen */
#include <pthread.h>

#define DFT_FILENAME    "/tmp/aaa"

#define FD_DIFF_STR "same file with different fd\n"
#define FD_SAME_STR "same file with same fd\n"

int
open_file_twice (const char *file,
                    int *fd1,
                    int *fd2)
{
    *fd1 = open (file, O_RDWR | O_TRUNC | O_CREAT | O_APPEND);
    assert (fd1 >= 0);
    *fd2 = open (file, O_RDWR | O_TRUNC | O_CREAT | O_APPEND);
    assert (fd2 >= 0);
    offsetof ();

    return 0;
}

void
test_same_file_with_diff_fd ()
{
    const char *str;
    int fd1, fd2;
    open_file_twice (DFT_FILENAME, &fd1, &fd2);
    str = (fd1 == fd2 ? FD_SAME_STR : FD_DIFF_STR);
    printf ("%s", str);
    close (fd1);
    close (fd2);
}

/* 
 * two file descriptor in single thread has disorder problem.
 * one file descriptor in multi thread has disorder problem too.
 */
void
single_thread_disorder_write_file ()
{
    int fd1;
    int fd2;

    open_file_twice (DFT_FILENAME, &fd1, &fd2);
    /* use sizeof (FD_SAME_STR) will write a unreadable character. */
    write (fd1, FD_SAME_STR, strlen(FD_SAME_STR));
    write (fd2, FD_DIFF_STR, strlen(FD_DIFF_STR));
    write (fd1, FD_SAME_STR, strlen(FD_SAME_STR));
    close (fd1);
    close (fd2);
}

/* the wield thing is : 
  * wirte alwayse success, but the real line < DFT_THREADS * 200. 
  */
void*
thread_func (void *arg)
{
    int fd = (int)arg;
    int i = 0;
    int len = strlen(FD_DIFF_STR);
    for (i=0; i<200; i++) {
        if (write (fd, FD_DIFF_STR, len) != len) {
            printf ("thread_func failed\n");
        }
    }
}


void
multi_thread_disorder_write_file ()
{
#define DFT_THREADS 50  /* too little threads can not have disorder error. e.g. 5 */
    int fd;
    pthread_t threads [DFT_THREADS];    
    fd = open (DFT_FILENAME, O_RDWR | O_CREAT | O_TRUNC | O_APPEND);

    int i;
    for (i=0; i<DFT_THREADS; i++)
        pthread_create (&threads[i], NULL, thread_func, (void*)fd);

    for (i=0; i<DFT_THREADS; i++)
        pthread_join (threads[i], NULL);

    close (fd);
}

int
main ()
{
    int fd1, fd2;

    test_same_file_with_diff_fd("/tmp/aaa");

    single_thread_disorder_write_file();
//    multi_thread_disorder_write_file();
    return 0;
}


