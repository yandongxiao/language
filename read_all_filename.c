#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>

int main()
{
	DIR *dip;
	struct dirent *dit;
	dip=opendir("/tmp");
	while((dit=readdir(dip)) != NULL) {
		printf("file:%s\n", dit->d_name);
	}
	closedir(dip);
}

