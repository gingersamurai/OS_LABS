
all: run

run: build/transmitter build/stat build/receiver
	./build/transmitter

build/%: %.c
	gcc $^ -o $@

clean:
	rm -rf build/* shmobj