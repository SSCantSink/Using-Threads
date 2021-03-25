tenthreads: tenthreads.c
	gcc -lpthread tenthreads.c -o tenthreads
clean:
	rm -f countprimes core *~