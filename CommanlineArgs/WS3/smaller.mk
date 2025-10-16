all: smaller.exe

smaller.exe : smaller.c 
	gcc smaller.c -o smaller.exe

run: smaller.exe #Command to run this: mingw32-make run NUM1=3 NUM2=5
	.\smaller.exe $(NUM1) $(NUM2)

clean:
	if exist smaller.exe del /F /Q smaller.exe