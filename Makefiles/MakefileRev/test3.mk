all: build

build: test3.exe

test3.exe: test3.o
	gcc test3.o -o test3.exe

test3.o: test2.c
	gcc test2.c -c -o test3.o

run: test3.exe
	test3.exe

clean: 
	if exist test3.o del /F /Q test3.o
	if exist test3.exe del /F /Q test3.exe