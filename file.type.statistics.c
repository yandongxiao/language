#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

/* TBD: check the return value. */

typedef struct {
    int reg_cnt;
    int dir_cnt;
    int chr_cnt;
    int blk_cnt;
    int lnk_cnt;
    int fifo_cnt;
    int socket_cnt;
} file_statistics_t;

typedef int (*handle_file_cb_t) (struct stat *buff, void *arg);

static void
usage ()
{
    fprintf (stderr, "./file_type_statistics dirname");
    exit(-1);
}

void
print_statistics (file_statistics_t *result)
{
    printf ("reg file : %d\n", result->reg_cnt);
    printf ("dir file : %d\n", result->dir_cnt);
    printf ("lnk file : %d\n", result->lnk_cnt);    
    printf ("blk file : %d\n", result->blk_cnt);
    printf ("chr file : %d\n", result->chr_cnt);
    printf ("fifo file : %d\n", result->fifo_cnt);
    printf ("socket file : %d\n", result->socket_cnt);
}

int handle_file (struct stat *buff, void *arg)
{
    file_statistics_t *statistics = arg;
    mode_t mode = buff->st_mode;
    if (S_ISREG(mode)) {
        statistics->reg_cnt++;
    }
    else if (S_ISBLK (mode)) {
        statistics->blk_cnt++;
    }
    else if (S_ISCHR(mode)) {
        statistics->chr_cnt++;
    }
    else if (S_ISDIR(mode)) {
        statistics->dir_cnt++;
    }
    else if (S_ISFIFO(mode)) {
        statistics->fifo_cnt++;
    }
    else if (S_ISLNK(mode)) {
        statistics->lnk_cnt++;
    }
    else if (S_ISSOCK(mode)) {
        statistics->socket_cnt++;
    }
    else {
        return -1;
    }
    return 0;
}

void
read_files (const char *dirname,
              handle_file_cb_t handle,
              void *arg)
{
    DIR *dir = opendir (dirname);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp (entry->d_name, ".") == 0 
            || strcmp (entry->d_name, "..") == 0)
            continue;

        struct stat buff;
        char filepath [512];
        int len = strlen (dirname);
        if (dirname[len-1] == '/')
            sprintf (filepath, "%s%s", dirname, entry->d_name);    /* note */
        else
            sprintf (filepath, "%s/%s", dirname, entry->d_name);    /* note */
        lstat (filepath, &buff);
        if (handle (&buff, arg) != 0) {
            fprintf (stderr, 
                    "error when handle %s\n", 
                    entry->d_name);
        }
        if (S_ISDIR(buff.st_mode)) {
            read_files (filepath, handle, arg);
        }

    }
    closedir (dir);
}

int
main (int argc, char **argv)
{
    if (argc != 2)
        usage ();
        
    struct stat buff;
    lstat (argv[1], &buff);
    if (! S_ISDIR (buff.st_mode))
        usage ();

    file_statistics_t statistics = {0};
    read_files (argv[1], handle_file, &statistics);
    print_statistics (&statistics);

    return 0;
}
