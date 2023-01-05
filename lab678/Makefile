all: build/control build/comput objclean

build/control: control.o map.o tree.o
	gcc $^ -llog -lzmq -o $@

build/comput: comput.o map.o tree.o
	gcc $^ -llog -lzmq -o $@

%.o: %.c
	gcc -c $^

objclean:
	rm -rf *.o

clean:
	rm -rf *.o control comput