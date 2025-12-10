all: run

test1.exe: test1.c
	gcc test1.c -o test1.exe

run: test1.exe
	./test1.exe

clean:
	if exist test1.exe del /F /Q test1.exe