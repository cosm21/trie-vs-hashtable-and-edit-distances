# Se genereaza cuvinte la intamplare
# a fost folosit pentru generarea testelor 9 pana la 12

import random
import string
from Levenshtein import distance as lev

fout = open("test.in", "w")

num_tests = 250000

fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')

for i in range(1, num_tests + 1):
    num = random.randint(10, 30);
    word1 = random.choices(string.ascii_lowercase, k=num);
    num = random.randint(10, 30);
    word2 = random.choices(string.ascii_lowercase, k=num);

    fout.write(''.join(word1) + ' ' + ''.join(word2) + '\n')


fout.close()
