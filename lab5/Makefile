
program1: program1.o libmymath1.so
	gcc program1.o -fPIC -L. -lmymath1 -lm -o program1

program1.o: program1.c
	gcc -c program1.c

libmymath1.so: mymath1.c
	gcc mymath1.c -shared -fPIC -o libmymath1.so

clean:
	rm -rf *.so program1 program2
