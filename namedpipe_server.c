#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <Fcntl.h>

int     Buffer_out;
int     count, i;
LPCTSTR pipeName = "\\\\.\\pipe\\ehsan";
HANDLE  hPipe;
FILE    *freOpenstream = NULL;
FILE    *test = NULL;

int main(int argc, char* argv[])
{
	/* step 1: create the named pipe. */
	hPipe = CreateNamedPipeA(pipeName,
		PIPE_ACCESS_INBOUND,
		PIPE_TYPE_BYTE | PIPE_WAIT,  /*If setting PIPE_NOWAIT, so ConnectNamedPipe and Readfile will not block again. */
		1,	/* every time you call CreateNamedPipeA, you create a instance. So 1 means only one instanced alloed to be created. */
		1024, 
		1024,
		1000,
		NULL);

	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("Server Pipe not created\n");
		exit(0);
	}
	else
		printf("Successful in creating server pipe\n");


	/* step2: waiting for client to connect to server */
	while (!ConnectNamedPipe(hPipe, (LPOVERLAPPED)NULL)) {
		printf("error\n");
	}

	/* step3: Read data from client */
	char buffer[1024];
	int ret;
	if (ReadFile(hPipe, buffer, 1024, &ret, NULL)) {
		buffer[ret] = '\0';
		printf("len=%d, cont=%s\n", ret, buffer);
	}
	else {
		perror("read error\n");
	}

	CloseHandle(hPipe);

	return 0;
}
