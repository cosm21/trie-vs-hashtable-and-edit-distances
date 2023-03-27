#!/bin/bash

# Verifica rezultatele implementarilor fata
# de iesirea de referinta

if [ $# -lt 1 ]
then
	echo "Need test number!"
fi

testnumber=$1
if ! [ -e "./in/test${testnumber}.in" ]
then
	echo "Test does not exist!"
	exit
fi

cp "./in/test${testnumber}.in" "test.in"
if ! [ -e "./out/test${testnumber}.out" ]
then
	echo "Output for test does not exist!"
	exit
fi
cp "./out/test${testnumber}.out" "ref.out"

./trie_test
mv test.out trie.out
diffres=$(diff trie.out ref.out)
if [ -n "$diffres" ]
then
	echo "Trie test FAIL!"
	echo $diffres
else
	echo "Trie test SUCCESS"
fi

./ms_test
mv test.out ms.out
diffres=$(diff ms.out ref.out)
if [ -n "$diffres" ]
then
	echo "Multiset test FAIL"
	echo $diffres
else
	echo "Multiset test SUCCESS"
fi
rm ref.out trie.out ms.out
