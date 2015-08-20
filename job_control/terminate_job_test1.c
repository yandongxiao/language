#include <stdio.h>
#include <windows.h>

/* Create a JOB object, add child process to it. */

int main()
{
	/* check If the current process already in a job */
	BOOL bInJob = FALSE;
	IsProcessInJob(GetCurrentProcess(), NULL, &bInJob);
	if (bInJob) {
		fprintf(stderr, "Process already in a job\n");
		return -1;
	}

	/* Create a Job Object */
	HANDLE myjob = CreateJobObjectA(NULL, "myjob");
	if (myjob == NULL) {
		fprintf(stderr, "CreateJobObjectA failed\n");
		return -1;
	}

	int i = 0;
	for (i = 0; i < 2; i++) {
		/* Create a child process */
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		char sz[] = "sleep 100";
		BOOL cc = FALSE;
		cc = CreateProcessA(NULL, sz, NULL, NULL,
			FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);	/* Note the flag */
		if (cc == FALSE) {
			fprintf(stderr, "CreateProcessA failed, Error Code <%d>\n", GetLastError());
			return -1;
		}

		/* Add the process to job */
		AssignProcessToJobObject(myjob, pi.hProcess);
		ResumeThread(pi.hThread);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

	}

	TerminateJobObject(myjob, 0);

	return 0;
}