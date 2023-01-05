all: build/control build/comput

build/control: control.o map.o tree.o
	gcc $^ -llog -lzmq -o $@

build/comput: comput.o map.o tree.o
	gcc $^ -llog -lzmq -o $@

%.o: %.c
	gcc -c $^

clean:
	rm -rf *.o build/*