all: hello.exe

hello.exe : hello.c	#target dependency, rebuild only if source code (dependency) is newer than target
	gcc hello.c -o hello.exe

run: hello.exe			#execute the last built source code, you can omit the dot backslash because cmd terminal does not need it
	.\hello.exe

clean:			#clean the directory
	if exist hello.exe del /F /Q hello.exe