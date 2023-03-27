# Se genereaza doua cuvinte care sunt scrise de doua ori,
# a doua oara in ordine inversa
# a fost folosit pentru a genera testul 8

import random
import string
from Levenshtein import distance as lev

fout = open("test.in", "w")

num_tests = 200000

fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')

num_tests /= 2
num_tests = int(num_tests)
for i in range(1, num_tests + 1):
    num = random.randint(10, 30);
    word1 = random.choices(string.ascii_lowercase, k=num);
    num = random.randint(10, 30);
    word2 = random.choices(string.ascii_lowercase, k=num);

    fout.write(''.join(word1) + ' ' + ''.join(word2) + '\n')

    word1 = ''.join(word1)
    word2 = ''.join(word2)

    fout.write(word2 + ' ' + word1 + '\n')
    
fout.close()
