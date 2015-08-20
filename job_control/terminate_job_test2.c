#include <stdio.h>
#include <windows.h>

/* Create a Process Group. */

int main()
{
	/* Create a process group */
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL cc = FALSE;
	//D:\\ubuntu_share\\developing\\4_0_working\\base\\example\\bin\\ttest.exe
	cc = CreateProcessA(NULL, "D:\\alias\\nsleep.bat", NULL, NULL,
		FALSE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi);	/* Note the flag */
	if (cc == FALSE) {
		fprintf(stderr, "CreateProcessA failed, Error Code <%d>\n", GetLastError());
		return -1;
	}

	/* generrate the signal, but how can we get the process ID. */
	DWORD pid = GetProcessId(pi.hProcess);
	GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, pid);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}