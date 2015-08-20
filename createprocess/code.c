

int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	fd_t child = CreateProcessA(NULL,
		"C:\\Users\\dxyan\\Documents\\Visual Studio 2013\\Projects\\base.process.c\\Debug\\test.bat 222", 
		NULL, NULL, TRUE, 0, NULL, NULL, 
		&si, &pi);
	if (INVALID_HANDLE_VALUE == child)
		printf("fail to create childprocess");
	int retcode = 0;
	i_waitpid(child, &retcode, -1);
	printf("exit_code = %d\n", retcode);

//	main_test();

}
