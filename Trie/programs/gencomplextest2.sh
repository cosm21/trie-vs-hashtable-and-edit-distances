#!/bin/bash

# Un program care genereaza un test in care se incearca stergerea unor
# cuvinte care nu exista

#cat "../tests/words_alpha.txt" | shuf | head -n 100000 | sort > tmp.in
comm -13 tmp.in "../tests/words_alpha.txt" > tmp2.in

sed "s/^/I /g" -i tmp.in
cat tmp.in | shuf > test.in

sed "s/^/D /g" -i tmp2.in
cat tmp2.in | shuf >> test.in
echo "E" >> test.in
