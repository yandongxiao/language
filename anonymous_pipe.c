/*
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa365141(v=vs.85).aspx
 * Asynchronous (overlapped) read and write operations are not supported by anonymous
 * pipes. This means that you cannot use the ReadFileEx and WriteFileEx functions with
 * anonymous pipes. In addition, the lpOverlapped parameter of ReadFile and WriteFile is
 * ignored when these functions are used with anonymous pipes.
 */

there are an examples in base.proc.c similar in windows examples. 
http://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
