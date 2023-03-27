# Extrage un cuvant dintr-o lista de cuvinte si ii face 
# cateva modificari
# a fost folosit pentru generarea testului 24

import random
from Levenshtein import distance as lev

fin = open("words_alpha.txt", "r")
fout = open("test.in", "w")

words = fin.readlines()

num_tests = 100000
fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')
for i in range(1, num_tests + 1):
    word1 = words[random.randint(0, len(words) - 1)]

    word1 = word1.replace('\n', '')
    word1 = list(word1)
    word2 = word1.copy()

    for i in range(1, 1 + 3):
        num = random.randint(0, len(word2) - 1);
        if(word2[num] != 'z'):
            val = ord(word2[num])
            val += 1
            word2[num] = chr(val)
        else:
            word2[num] = 'a'

    fout.write(''.join(word1) + " " + ''.join(word2) + "\n")

fin.close()
fout.close()
