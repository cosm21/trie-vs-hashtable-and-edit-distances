# Program care citeste cate doua cuvinte dintr-o lista
# si genereaza teste pe baza acestora
# a fost folosit pentru testul 23

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
    word2 = words[random.randint(0, len(words) - 1)]
    
    word1 = word1.replace('\n', '')
    word2 = word2.replace('\n', '')

    fout.write(word1 + " " + word2 + "\n")

fin.close()
fout.close()
