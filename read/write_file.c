#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd = open("/tmp/abc", O_RDWR);
	char* buffer="nihao";
	int ret = write(STDOUT_FILENO, buffer, 5);
	fsync(fd);
}
