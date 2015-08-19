/*
 *  read_file
 *      whenever you read a normal file, read will not be blocked.
 *    when the file is empty or nothing to read, ret=0. NOTE: buf[0] is not initialized by '\0'.
 *     when the file has just a character, ret=2. buf[1]='\n'. NOTE: the buf[2] is initialized by '\0'.
 *     So buf[ret]='\0' is necessary, and you may want to remove the '\n'.
 *    O_CREAT : create a new file when it dose not exist.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int 
read_file(int argc, char **argv)
{
    int ret = 0;
    char buf[1024];
    int fd;
    int flag = O_CREAT | O_RDWR;

    if(argc == 2)
        flag = flag | O_NONBLOCK;

    fd = open("/tmp/aaa", flag);
    if(fd < 0 )
        perror("open : ");
    buf[2]='X';
    ret = read(fd, buf, 1024);
    if(ret < 0) {
        printf("read error \n");
    }
    else if(0 == ret){
        printf("nothing to read.\n");
    }
    else {
        buf[ret] = '\0';
        printf("len=%d, contents=%s", ret, buf);
    }
    
    close(fd);
    return 0;
}

int 
main(int argc, char **argv) {
    read_file(argc, argv);
}
