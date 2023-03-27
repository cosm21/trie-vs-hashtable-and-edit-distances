CC=gcc

build: trie_test ms_test

run-p1: trie_test
	./trie_test

run-p2: ms_test
	./ms_test

trie.o: trie.c
	$(CC) -c trie.c -o trie.o

trie_test.o: trie_test.c
	$(CC) -c trie_test.c -o trie_test.o

trie_test: trie.o trie_test.o
	$(CC) trie_test.o trie.o -o trie_test

LinkedList.o: LinkedList.c
	$(CC) -c LinkedList.c -o LinkedList.o

Hashtable.o: Hashtable.c
	$(CC) -c Hashtable.c -o Hashtable.o

multiset.o: multiset.c
	$(CC) -c multiset.c -o multiset.o

ms_test: multiset.o Hashtable.o LinkedList.o ms_test.c
	$(CC) multiset.o Hashtable.o LinkedList.o ms_test.c -o ms_test

ht_test: Hashtable.o LinkedList.o ht_test.c
	$(CC) Hashtable.o LinkedList.o ht_test.c -o ht_test

clean:
	rm -f *.o
	rm -f trie_test ms_test

.PHONY: clean build run-p1 run-p2
