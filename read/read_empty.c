/*
	/usr/include/asm-generic/errno-base.h
	/usr/include/asm-generic/errno.h
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd = open("/tmp/abc", O_RDONLY);
	char buffer[10];
	int ret = read(STDIN_FILENO, buffer, 10);
}
