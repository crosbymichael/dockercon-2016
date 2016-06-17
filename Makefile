
all:
	gcc -o cloexec cloexec.c
	gcc -o parent parent.c

clean:
	rm -f cloexec
	rm -f parent
	rm -f exit-fifo
