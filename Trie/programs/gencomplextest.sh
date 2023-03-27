#!/bin/bash

# Genereaza un test cu un numar mare de inserari
# urmat apoi de lookup-uri in alta ordine, apoi
# de delete-uri in alta ordine

if [ $# -lt 2 ]
then
	echo "Need arguments!"
	exit
fi

#cat "../tests/words_alpha.txt" | shuf | head -n $1 > tmp.in

cp tmp.in tmp2.in
sed "s/^/I /g" -i tmp2.in
cat tmp2.in >> test.in

echo "P" >> test.in

#cat tmp.in | shuf > tmp2.in
cat tmp.in > tmp2.in
sed "s/^/L /g" -i tmp2.in
cat tmp2.in >> test.in

#cat tmp.in | shuf > tmp2.in
cat tmp.in > tmp2.in
sed "s/^/D /g" -i tmp2.in
cat tmp2.in >> test.in

echo "P" >> test.in
echo "E" >> test.in

mv test.in "./in/test$2.in"
#rm -f tmp.in tmp2.in
rm -f tmp2.in
