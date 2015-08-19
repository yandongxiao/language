/*
 * pipe can be inherited, but the max created pipe pairs is 512 in process.
 * same as 1024 file descriptor
 */
#include <unistd.h>
#include <stdio.h>

int 
main(int argc, char **argv) {
    int i = 0;
    while(1) {
    	int p[2];
        if(pipe(p))
    		break;
	    i++;
//	close(p[0]);
//	close(p[1]);
    	printf("pipe created num = %d\n", i);
    }
    return 0;
}
