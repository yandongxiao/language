#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <assert.h>

#define WRITE_FILE(f, buffer, str, i, j) \
	do {			\
		sprintf(buffer, str, i, j);		\
		_write(_fileno(f), buffer, strlen(buffer));	\
	}while(0)

#define READ_CHECK(handle, i, f, buffer, error, overlap) \
	do {		\
		error = GetLastError();				\
		if ( error == ERROR_NO_DATA ) {		\
			WRITE_FILE(f, buffer, "%d %d there is not data in pipe now\n" ,i, GetTickCount());	\
		} else if (error == ERROR_BROKEN_PIPE) {		\
			WRITE_FILE(f, buffer, "%d server have close the wirte end of pipe\n", i, GetTickCount());	\
			fclose(f);		\
			exit(-1);		\
		}else if (error == ERROR_MORE_DATA) {		\
			WRITE_FILE(f, buffer, "%d %d the read message is too long.\n", i, GetTickCount());	\
		} else if(error == ERROR_IO_PENDING) {	\
			int num_read = 0;		\
			char tmp[1024];			\
			(error = WaitForSingleObject(overlap.hEvent, -1));	\
			switch(error) {   	\
				case WAIT_OBJECT_0:  \
					if (GetOverlappedResult(handle, &overlap, &num_read, FALSE))		\
					{				\
						buffer[num_read] = '\0';		\
						sprintf(tmp, "ERROR_IO_PENDING over: %d-%d:%s", i, GetTickCount(), buffer);		\
						_write(_fileno(f), tmp, strlen(tmp));				\
						i++;		\
					}			\
					break;		\
				case ERROR_IO_PENDING:		\
					CancelIo(handle);		\
					WRITE_FILE(f, buffer, "%d %d there is a ERROR_IO_PENDING error\n", i, GetTickCount());	\
					break;		\
				default:			\
					sprintf(tmp, "%d-%d:fail to wait io %d\n", i, GetTickCount(), error);		\
					_write(_fileno(f), tmp, strlen(tmp));				\
			}		\
		} else {		\
			WRITE_FILE(f, buffer, "%d %d there is a read error\n", error, GetTickCount());		\
			fclose(f);	\
			exit(-1);		\
		}		\
	}while(0)

	/*
		http://msdn.microsoft.com/en-us/library/windows/desktop/aa365603(v=vs.85).aspx
	*/
int
read_method1(HANDLE handle, int cnt, FILE *f, char *buffer, int size) {
		int num = 0;
		int error = 0;
		OVERLAPPED overlap;
		ZeroMemory(&overlap, sizeof(OVERLAPPED));

		HANDLE hevent = CreateEvent(
         NULL,    // default security attribute 
         TRUE,    // manual-reset event 
         FALSE,    // initial state = non-signaled 
         NULL);   // unnamed event object 
		assert(hevent != NULL);
		overlap.hEvent = hevent;
		
		if(!ReadFile(handle, buffer, size, &num, &overlap)) {
			int ttcnt = cnt;
			READ_CHECK(handle, cnt, f, buffer, error, overlap);
			if(cnt > ttcnt)
				return 0;
			return -1;
		} else {
			buffer[num] = '\0';
			char tmp[1024];
			sprintf(tmp, "%d-%d:%s", cnt, GetTickCount(), buffer);
			_write(_fileno(f), tmp, strlen(tmp));
			return 0;
		}
}

int
read_method2(HANDLE handle, int cnt, FILE *f, char *buffer, int size) {
		int error;
		if(NULL == fgets (buffer, size, stdin)) {
			OVERLAPPED overlap;
			READ_CHECK(handle, cnt, f, buffer, error, overlap);
			return -1;
		} else {
			char tmp[1024];
			sprintf(tmp, "%d-%d:%s", cnt, GetTickCount(), buffer);
			_write(_fileno(f), tmp, strlen(tmp));
			return 0;
		}
}

int main(int argc, char **argv)
{
	char str[1024];
	char buffer[1024];
	printf("args:%s\n", argv[1]);
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	int i=0;
	FILE *f = fopen("D:\\out", "a");
	setvbuf(stdin, NULL,_IOLBF, 1024);
	for(i=0; i<1000*1000;) {
		if(read_method1(handle, i, f, buffer, 1024) == 0)
			i++;
//		if(read_method2(handle, i, f, buffer, 1024) == 0)
//			i++;
		Sleep(atof(argv[1])*100);
	}
	_write(_fileno(f), "\ndone\n", 6);
	fclose(f);
	exit(10);
}