
program2: program2.o libmymath1.so libmymath2.so
	gcc $< -ldl -lm -o $@
program1: program1.o libmymath2.so
	gcc $< -fPIC -L. -lmymath2 -lm -o $@

program%.o: program%.c
	gcc -c $^

libmymath%.so: mymath%.c
	gcc $^ -shared -fPIC -o $@

clean:
	rm -rf *.so *.o program1 program2
