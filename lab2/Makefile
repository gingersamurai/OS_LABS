CFLAGS=-Wall -Werror -Wextra

all: parent child
	./build/parent

parent: parent.c
	gcc parent.c -o build/parent

child: child.c
	gcc child.c -o build/child

clean:
	rm -rf *.txt