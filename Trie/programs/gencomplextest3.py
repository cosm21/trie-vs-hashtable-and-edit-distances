#!/bin/python

import random

# Acest program a fost folosit pentru generarea testelor
# 23 si 24

fin = open("../tests/words_alpha.txt", "r")
fout = open("test.in", "w")

lines = fin.readlines()

for i in range(1, 1 + 100000):
    num = random.randint(0, len(lines) - 1)
    word = lines[num]
    word = word.replace('\n', '')
    fout.write("I " + word + "\n")

for i in range(1, 1 + 300000):
    num = random.randint(0, len(lines) - 1)
    word = lines[num]
    word = word.replace('\n', '')

    op = random.randint(0, 1000000)
    if(op % 1000 == 0):
        fout.write("P\n")
    elif(op % 3 == 0):
        fout.write("I ");
    elif(op % 3 == 1):
        fout.write("L ")
    elif(op % 3 == 2):
        fout.write("D ")

    if(op % 1000 != 0):
        fout.write(word + '\n');

fin.close()
fout.close()
