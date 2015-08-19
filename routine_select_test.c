#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

/*
 * no matter open or socket function, the created file descripter has the
 * same behavior. select will wait over 2 sec.
 * open read immediately
 * pipe read specially: 
 */
int main() {
//	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
//	int sock = open("/tmp/ttt", O_RDWR);
	int pp[2];
    int sock;
	fd_set wm;
	struct timeval s;

	pipe(pp);
	sock = pp[0];
	if(sock < 0)
		perror("socket");
	FD_ZERO(&wm);
	FD_SET(sock, &wm);
	s.tv_sec = 2;
	s.tv_usec = 0;
	
	int nr = select(sock + 1, NULL, &wm, NULL, &s); 	/* plus 1. */
	if(nr < 0 )
		perror("select");
	else if(nr == 0)
		 printf(" time out.\n");
	else
		printf(" event happend\n");
}
