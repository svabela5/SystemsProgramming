all: demo full

demo:
    gcc -Wall FullDemo.c -o demo

full: 
    gcc -DFULL -Wall FullDemo.c -o full

runDemo: demo
	.\demo

runFull: full
	.\full