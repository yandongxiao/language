@ECHO OFF

FOR %%A IN (%*) DO (
	IF "%%A" == "start"		call:start
	IF "%%A" == "stop"		call:stop
	IF "%%A" == "status"	call:status
	IF "%%A" == "restart"	call:restart
)
goto:eof

:start
	echo start
goto:eof

:stop
	echo stop
goto:eof

:status
	echo status
goto:eof

:restart
	call:start
	call:stop
goto:eof