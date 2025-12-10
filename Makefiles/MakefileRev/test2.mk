all: build

build: test2.exe

test2.exe: test2.c
	gcc test2.c -o test2.exe

run: test2.exe
	./test2.exe

clean:
	if exist test2.exe del /F /Q test2.exe