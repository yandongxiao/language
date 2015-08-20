#include <windows.h>
#include <process.h>
#include <stdio.h>


HANDLE    hPipe;
const int BUFSIZE = 10;
int Buffer_in;
int       count;

int main(int argc, char* argv[])
{
	/* step1: open named pipe. */
	hPipe = CreateFileA("\\\\.\\pipe\\ehsan", // this machine
		GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("Server Pipe not found\n");
		goto done;
	}
	else
		printf("Successful in finding server pipe\n");

	/* step2: redirect handle to stdout*/
	int stream = _open_osfhandle((long)hPipe, 0);
	if (stream == -1) {
		perror("_open_osfhandle");
		exit(1);
	}

	if (_dup2(stream, 1) == -1)
	{
		perror("Can't _dup2 stdout");
		exit(1);
	}

	int ret = setvbuf(_fdopen(stream, "w"), NULL, _IOLBF, 1024);	/*NOTE: It is useless*/
	if (0 != ret)
	{
		printf("invalid set\n");
	}
	printf("helloworld\n");
	_flushall();


	_close(stream);		/* there is no need to close hPipe */
	return 0;
done:
	return -1;
}
