#!/bin/bash

# Acest script a fost folosit pentru generarea
# iesirilor de referinta
# Pentru un testul cu numarul specificat, ruleaza implementarea
# de referinta si apoi copiaza rezultatul in folderul de iesiri corecte,
# cu acelasi numar dat

if [ $# -lt 1 ]
then
	echo "need test number"
	exit
fi

in="./in/test$1.in"
if ! [ -f "$in" ]
then
	echo "test does not exist!"
	exit
fi
out="./out/test$1.out"
cp $in test.in
python ../ref.py
cp test.out $out
