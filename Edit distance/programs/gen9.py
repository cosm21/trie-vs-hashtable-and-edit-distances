# Se genereaza un cuvant, apoi se schimba cateva litere din acesta
# a fost folosit pentru a genera testele 13 pana la 17

import random
import string
from Levenshtein import distance as lev

fout = open("test.in", "w")

num_tests = 100000

fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')

for i in range(1, num_tests + 1):
    num = random.randint(10, 30);
    word1 = random.choices(string.ascii_lowercase, k=num);
    word2 = word1.copy()

    for i in range(1, 1 + 9):
        num = random.randint(0, len(word2) - 1);
        if(word2[num] != 'z'):
            val = ord(word2[num])
            val += 1
            word2[num] = chr(val)
        else:
            word2[num] = 'a'


    word1 = ''.join(word1)
    word2 = ''.join(word2)

    fout.write(word1 + ' ' + word2 + '\n')
    
fout.close()
