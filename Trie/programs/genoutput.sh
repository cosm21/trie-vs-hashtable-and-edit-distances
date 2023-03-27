#!/bin/bash

# Folosind implementarea de referinta, genereaza
# iesirea corespunzatoare testului dat

if [ $# -lt 1 ]
then
	echo "Needs argmunets"
	exit
fi

cp "./../in/test$1.in" test.in
python ../ref.py
cp test.out "./../out/test$1.out"
