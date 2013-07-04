all:
	gcc -o test test.c
	gcc -o test-1 test-1.c
	gcc -o bfd bfd.c -lbfd
	gcc -o bfd_dumpfun bfd_dumpfun.c -lbfd
	gcc -c whocallme.c -Wall
	ar -q libwhocallme.a whocallme.o
	gcc -o test-2 test-2.c -lbfd -L. -lwhocallme

clean:
	rm -f \
		test test-1 bfd bfd_dumpfun \
		whocallme.o libwhocallme.a test-2
