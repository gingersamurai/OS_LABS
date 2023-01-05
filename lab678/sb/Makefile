all: server client

%: %.c
	gcc $^ -lzmq -llog -o $@

clean:
	rm -rf server client