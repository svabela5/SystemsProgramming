all: average.exe

average.exe : average.c
	gcc average.c -o average.exe

# Example usage:
# mingw32-make run ARGS="3 5 7 9 11"
run: average.exe
	.\average.exe $(ARGS)

clean:
	if exist average.exe del /F /Q average.exe
