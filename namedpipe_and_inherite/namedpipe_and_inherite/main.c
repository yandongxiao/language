#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include <stdbool.h>
#include <assert.h>
#include <io.h>
#include <Fcntl.h>

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
/*
 * 命名管道可以实现异步通信，所以我们使用CreateNamedPipeA和CreateFile两个函数来
 * 分别创建命名管道的server端和client端。
 * 至于匿名管道，windows下给定的example已经相当有用了.
 */

static const char * pipename = "\\\\.\\pipe\\jhnamedpipe";

int
create_pipe(HANDLE pipe[2]) {
	/* 步骤1. 创建server端*/
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	pipe[0] = CreateNamedPipeA(
		pipename,			/* 命名管道的名称 */
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,	/* 管道的权限,它同时指定了server和client对管道的读写权限. */
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE |	/* 将一次write操作当作一个消息，read时也读取一个消息 */
		PIPE_NOWAIT,		/* 非阻塞式管道. */
		PIPE_UNLIMITED_INSTANCES,	/* 该命名管道的实例的个数. */
		1024*1024,		/* 我想如果设置为0的话，写入管道的内容将不会被保存. */
		1024*1024,
		0,			/* 目前这个参数对我们没用. */
		&saAttr);	/* 我们希望child process 能够继承 */
	if (INVALID_HANDLE_VALUE == pipe[0]) {
		ErrorExit(TEXT("CreateNamedPipeA"));
	}

	/* 步骤2. 创建client端 */
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	pipe[1] = CreateFileA(
		pipename,		/* 管道的名称 */
		GENERIC_WRITE | GENERIC_READ,	/* 根据管道的权限，我们这里可以要求对管道拥有读写权限 */
		0,		/* 不需要让其它进程来打开这个管道.  */
		&saAttr, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);
	if (INVALID_HANDLE_VALUE == pipe[1]){
		ErrorExit(TEXT("CreateFileA"));
	}
	return 0;
}

/*
 * fd[0] 负责从管道读.
 * fd[1] 负责向管道写.
 * read_fd :  父进程准备从管道读.
 * write_fd : 父进程准备向管道写
 */
HANDLE
create_process(char *path, char *args, HANDLE read_fd[2], HANDLE write_fd[2]) {
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFOA siStartInfo;
	BOOL bSuccess = FALSE;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFOA);

	assert(read_fd != write_fd);
	if (read_fd) {
		siStartInfo.hStdOutput = read_fd[1];
		if (!SetHandleInformation(read_fd[0], HANDLE_FLAG_INHERIT, 0))	/* 读管道就没必要继承了. */
			ErrorExit(TEXT("SetHandleInformation"));
	}
	if (write_fd) {
		siStartInfo.hStdInput = write_fd[1];		/* 这个管道本来就无所谓读端和写端，所以填写write_fd[1/0] 都行*/
		if (!SetHandleInformation(write_fd[0], HANDLE_FLAG_INHERIT, 0))	/* 写管道就没必要继承了. */
			ErrorExit(TEXT("SetHandleInformation"));
	}
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	char buffer[1024];
	sprintf_s(buffer, 1024, "%s %s", path, args);    /* the parameter must be started with ' ' */
	bSuccess = CreateProcessA(NULL,
		buffer, NULL, NULL,
		TRUE,
		0, NULL, NULL,
		&siStartInfo,
		&piProcInfo);
	if (!bSuccess) {
		ErrorExit(TEXT("CreateFileA"));
	}
	
	CloseHandle(piProcInfo.hThread);
	return piProcInfo.hProcess;
}

/*
 * 1. 必须重定向子进程的标准输行，在我们的标准输出上找不到子进程输出的内容。
 * 2. windows下调用setvbuf函数设置为行缓冲是不起作用的，
 *    在官方文件中也确实看到了 for Win32, the behavior is the same as _IOFBF - Full Buffering.
 * 3. scanf、fgets、ReadFile读取函数的区别：scanf每逢遇到空白字符或者换行符时返回，fgets在遇到换行符
 *	  或end-of-file时返回，ReadFile返回的情况在windows官网上说了，The number of bytes requested is read,
 *	  A write operation completes on the write end of the pipe.  
 *    An asynchronous handle is being used and the read is occurring asynchronously.
 *    An error occurs。scanf和fgets是sync，而ReadFile则可以是async和sync两种情况。
 * 注意事项：
 * 4. 创建管道的SERVER端和CLINET端时，都要传递SECURITY_ATTRIBUTES数据结构。它表示该句柄允许被inherit，
 *    在调用createprocess，设置bInheritHandle为True即可。
 * 5. 创建管道的SERVER端和CLINET端时,设置FILE_FLAG_OVERLAPPED属性表示允许进行异步读取。这还不够，在ReadFile
 *   时还要传递OVERLAPPED这样的一个结构。
 * 6. ReadFile返回false时，GetlastError返回ERROR_IO_PENDING，该怎么办？
 *    http://wenzhang.baidu.com/article/view?key=97edf98fac9d9ccd-1410605442 该连接介绍了一般的处理过程，我们也
 *    可以调用CancelIo函数。注意不这样处理，ReadFile都会返回这样的同一个错误。
 * 7. ReadFile返回false时，GetlastError返回ERROR_BROKEN_PIPE，该怎么办？ 表示pipe的一端已经关闭。
 * 8. 父进程连续发送十条信息，注意因为是Full Buffering,每次发送信息的结尾要调用FlushFileBuffers或fflush函数；
 *    子进程利用ReadFile读取数据，为了使得。
 * 
 * windows下重定向标准输出的方法：
 *     int old = _dup(1);
 *     assert(-1 != old);
 *     int stream = _open_osfhandle((long)fd[0], 0);
 *     assert(-1 != stream);
 *     assert(-1 != _dup2(stream, 1));
 *     printf("helloworld\n");
 *     fflush(stdout);
 *     assert(-1 != _dup2(old, 1));
 * 注意fflush(stdout)的作用，如果没有清空输出缓冲区，那么接下来的_dup2(old, 1));就不会起作用。或者说
 * 你在随后的printf操作不会有什么效果。
 */
void test_write_to_pipe_by_stdout(char *path, char *args, float sec) {
	HANDLE fd[2];
	create_pipe(fd);
	create_process(path, args, NULL, fd);	/* 0 means child process dont sleep.*/
	
	CloseHandle(fd[1]);		/* 无论何时都是关闭fd[1]. */

	char buffer[1024];
	int i = 0;
	int old = _dup(1);
	assert(-1 != old);
	int stream = _open_osfhandle((long)fd[0], 0);
	assert(-1 != stream);
	assert(-1 != _dup2(stream, 1));

	for (i = 0; i < 100; i++) {
		static char XXX[1024];
		sprintf_s(buffer, 1024, "whelloworld : %d\n", i + 1);
		if (printf("%s", buffer) < 0) {
			int error = GetLastError();
			if (GetLastError() == ERROR_BROKEN_PIPE) {
				assert(-1 != _dup2(old, 1));
				printf("server have close the read end of pipe\n");
				CloseHandle(fd[0]);
				return;
			} else
			{
				ErrorExit(TEXT("printf"));
			}
		}
		fflush(stdout);
		Sleep(100 * sec);
	}
	assert(-1 != _dup2(old, 1));
	_close(old);
	_close(stream);
	CloseHandle(fd[0]);
	printf("test_write_to_pipe_by_stdout\n");
}


void test_write_to_pipe_by_WriteFile(char *path, char *args, float sec) {
	HANDLE fd[2];
	create_pipe(fd);
	create_process(path, args, NULL, fd);	/* 0 means child process dont sleep.*/

	CloseHandle(fd[1]);		/* 无论何时都是关闭fd[1]. */

	char buffer[1024];
	int i = 0;
	for (i = 0; i < 100; i++) {
		sprintf_s(buffer, 1024, "whelloworld : %d\n", i + 1);
		OVERLAPPED overlap;
		ZeroMemory(&overlap, sizeof(OVERLAPPED));
		int num = 0;
		
		if (!WriteFile(fd[0], buffer, strlen(buffer), &num, &overlap)) {
			int error = GetLastError();
			if (error == ERROR_BROKEN_PIPE) {
				printf("server have close the read end of pipe\n");
				CloseHandle(fd[0]);
				return;
			}
			else if (error == ERROR_NO_DATA){
				printf("pipe is being close\n");
				CloseHandle(fd[0]);
				return;
			}
			else
			{
				ErrorExit(TEXT("WriteFile"));
			}
		}
//		FlushFileBuffers(fd[0]);
		Sleep(100 * sec);
	}
//	FlushFileBuffers(fd[0]);

//	Sleep(10000);
	CloseHandle(fd[0]);
	printf("test_write_to_pipe_by_WriteFile\n");
}


/*
 * 1. SERVER端不间断的从管道中读数据，有时ReadFile返回false, GetLastError返回的是ERROR_NO_DATA错误信息.
 * 2. SERVER端每隔100ms从管道中读数据，每次都能读取成功。
 * 3. 从管道内一次性读取的数据是一行, 所有写入管道的内容都能够被正确读取。貌似与创建管道时设定的输入输出缓冲区
 *    没有什么关系。
 */
void
test_read_from_pipe(char *path, char *args) {
	HANDLE fd[2];
	create_pipe(fd);
	create_process(path, "0", fd, NULL);	/* 0 means child process dont sleep.*/

	/* 
	 * 目前管道的读端有一个handle，而管道的写端有两个handle.最好是关闭父进程的写端.
	 * 否则，ERROR_BROKEN_PIPE的状态就不可能达到，因为父进程一直维护着一对完好的
	 * 读端和写端。
	 */
	CloseHandle(fd[1]);		

	char buffer[1024];
	int num = 0;
	OVERLAPPED overlap;
	ZeroMemory(&overlap, sizeof(OVERLAPPED));

	int i = 0;
	for (i = 0; i < 10; ) {
		Sleep(atoi(args) * 100);
		if (!ReadFile(fd[0], buffer, 1024, &num, &overlap)) {
			int error = GetLastError();
			if ( error == ERROR_NO_DATA ) {
				printf("there is not data in pipe now\n");
			}else if (error == ERROR_BROKEN_PIPE) {
				printf("server have close the wirte end of pipe\n");
				CloseHandle(fd[0]);
				return;
			}else if (errno == ERROR_MORE_DATA) {
				printf("the read message is too long.\n");
			} else {
				ErrorExit(TEXT("ReadFile"));
			}
			continue;
		}
		if (num == 0) {
			buffer[0] = '\0';
		}else {
			if ('\n' == buffer[num - 1])
				buffer[num - 1] = '\0';
			else
				buffer[num] = '\0';
		}
		i++;		
		printf("read content is : %s\n", buffer);
	}
}

int main() {
//	test_read_from_pipe("D:\\ubuntu_share\\bat\\test_read_from_pipe.bat", "0");
//	test_read_from_pipe("D:\\ubuntu_share\\bat\\test_read_from_pipe.bat", "1");

	/*
	 * Server 端分别以printf和WriteFile两种方式输出数据，Client端以ReadFile读取数据。测试结果如下：
	 *   1. printf方式。client每次从pipe中取出所有数据，由于发送较快，所以导致client端用了6次就读完了所有数据。显示产生ERROR_IO_PENDING，
	 *      直到程序结束为止,此时产生ERROR_IO_BROKEN错误。注意不存在阻塞。
	 * 所以存在，client端最后一句的输出是“server have close the wirte end of pipe”
	 *   2. WriteFile方式。client每次要么从pipe中读取处一条数据要么读到的是ERROR_IO_PENDING（因为server端正在写或者将要写嘛）。
	 *   3. server端写的速度变慢，client读取的是ERROR_IO_PENDING状态。 存在丢失数据的问题！！
	 *   
	 *  
	 * Server端分别以printf和WriteFile两种方式输出数据，Client端以fgets读取数据。测试结果如下：（估计会阻塞）
	 *   1. printf方式。client每次读取处一行数据，每隔一秒读取一次
	 *	 2. WriteFile方式。这里竟然没有打印出内容，说是什么管道正在被关闭。
	 */
//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "1", 0);
//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "1", 0);

	test_write_to_pipe_by_stdout("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "0.5", 2);


//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "0.5", 1);
//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "0.5", 1);

//	test_write_to_pipe_by_stdout("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "0.5", 1);
//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "0.5", 1);

	/*
	 * Server 端分别以printf和WriteFile两种方式输出数据，Client端以fgets读取数据。不过这次改为client不停的从管道拿数据。
	 * 1. printf方式。 client不停的调用ReadFile，比较奇怪的地方是printf到终端的内容，在第二次重定向标准输出时，里面的内容直接输出了。
	 */
//	test_write_to_pipe_by_stdout("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "1", 2);
//	test_write_to_pipe_by_WriteFile("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "1", 2);



//	test_write_to_pipe("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "5");
//	test_write_to_pipe("C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.exe", "5");
//	Sleep(1000 * 2000);

}