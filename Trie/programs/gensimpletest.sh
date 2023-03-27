#!/bin/bash

# Un program care genereaza un test foarte
# simplu, pornind de la un fisier care are cate un cuvant
# pe linie

if [ $# -lt 1 ]
then
	echo "Need a file."
	exit
fi
fin=$1
if ! [ -e "$fin" ]
then
	echo "File does not exist."
fi

cp $fin tmp.in
sed "s/^/I /g" -i tmp.in
echo "P" >> tmp.in
echo "E" >> tmp.in
mv tmp.in "./in/test.in"

#cp $fin tmp.out
#sed "s/^/Insert: \"/g" -i tmp.out
#sed "s/$/\"./g" -i tmp.out
#cp tmp.out "./out/test.out"
#cat $fin | sort > tmp.out
#sed "s/^/Print: \"/g" -i tmp.out
#sed "s/$/\"./g" -i tmp.out
#cat tmp.out >> "./out/test.out"
#rm tmp.out
