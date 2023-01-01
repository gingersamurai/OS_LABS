all: exe lib

exe: hello.h main.c lib
	gcc main.c -fPIC -ldl -o hello 

lib: hello.h hello.c
	gcc hello.c -shared -fPIC -o libhello.so
clean:
	rm -rf hello libhello.so