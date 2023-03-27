CC=gcc

build: test_uk test_basic

run-p1: test_basic
	./test_basic

run-p2: test_uk
	./test_uk

test_uk: test_uk.c distance.o
	$(CC) test_uk.c distance.o -o test_uk

test_basic: test_basic.c distance.o
	$(CC) test_basic.c distance.o -o test_basic

distance.o: distance.c
	$(CC) -c -o distance.o distance.c

clean:
	rm -f *.o
	rm -f test_uk test_basic

.PHONY: clean build run-p1 run-p2
