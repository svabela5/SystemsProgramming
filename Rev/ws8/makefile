all: build

build: out.exe 

out.exe: messages.o ws08c.c 
	gcc ws08c.c messages.o -o out.exe

messages.o: messages.c
	gcc messages.c -c -o messages.o

run: out.exe
	./out.exe

clean:
	if exist messages.o del /F /Q messages.o
	if exist out.exe del /F /Q out.exe