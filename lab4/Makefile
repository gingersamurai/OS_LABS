.PHONY: clean

parent: parent.c child
	gcc parent.c -lpthread -o build/parent
child: child.c
	gcc child.c -lpthread -o build/child

clean:
	rm -rf build/*