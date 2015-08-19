#include <unistd.h>
#include <stdio.h>

/* The maximum number of files that a process can have open at any time. */
int main(void) {
	long size = sysconf(_SC_OPEN_MAX);
	printf("_SC_OPEN_MAX == %ld\n", size);  /* 1024 */
}
