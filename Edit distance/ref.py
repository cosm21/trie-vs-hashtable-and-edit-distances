#!/bin/python

# pentru editdistance https://pypi.org/project/editdistance/
# pentru pyxDamerauLevenshtein https://pypi.org/project/pyxDamerauLevenshtein/

import pyxdameraulevenshtein as dmlvs
import editdistance as lvs
import math

fin = open("test.in", "r")
fout = open("test.out", "w")

lines = fin.readlines()

print(lines.pop(0).replace('\n', ''))
print(len(lines))

for line in lines:
    words = line.split()
    
    words[0] = words[0].replace('\n', '')
    words[1] = words[1].replace('\n', '')

    dist_lvs = lvs.eval(words[0], words[1])
    dist_dmlvs = dmlvs.damerau_levenshtein_distance(words[0], words[1])

    fout.write(str(dist_lvs) + " " + str(int(dist_dmlvs)) + "\n")

fin.close()
fout.close()
