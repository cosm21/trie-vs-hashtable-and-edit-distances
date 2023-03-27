#!/bin/bash

# Acest program primeste un numar si valideaza corectitudinea algoritmilor
# fata de referinta pe acel test

if [ $# -lt 1 ]
then
	echo "need test number"
	exit
fi

in="./in/test$1.in"
if ! [ -f "$in" ]
then
	echo "input does not exist"
	exit
fi
out="./out/test$1.out"
if ! [ -f "$out" ]
then
	echo "output for test does not exist"
	exit
fi

cp $in test.in
cp $out ref.out

./test_basic
mv test.out basic.out

./test_uk
mv test.out uk.out

dif=$(diff basic.out ref.out)
if [ -n "$dif" ]
then
	echo "basic FAIL"
else
	echo "basic SUCCESS"
fi

dif=$(diff uk.out ref.out)
if [ -n "$dif" ]
then
	echo "uk FAIL"
else
	echo "uk SUCCESS"
fi
