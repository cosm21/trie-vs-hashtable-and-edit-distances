# Se genereaza un cuvant, apoi se transpune o litera din acesta
# a fost folosit pentru a genera testul 3

import random
import string
from Levenshtein import distance as lev

fout = open("test.in", "w")

num_tests = 100000

fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')

for i in range(1, num_tests + 1):
    num = random.randint(5, 20);
    word1 = random.choices(string.ascii_lowercase, k=num);
    word2 = word1.copy()
    num = random.randint(0, len(word2) - 2);
    word2[num], word2[num + 1] = word2[num + 1], word2[num]

    word1 = ''.join(word1)
    word2 = ''.join(word2)

    fout.write(word1 + ' ' + word2 + '\n')
    
fout.close()
