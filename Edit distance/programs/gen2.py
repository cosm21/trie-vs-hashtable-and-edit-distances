# Generator care copiaza acelasi cuvant
# a fost folosit pentru a genera testul 1

import random
import string
from Levenshtein import distance as lev

fout = open("test.in", "w")

num_tests = 100000

fout.write(str(num_tests) + ' ')
fout.write(str(-1) + '\n')

for i in range(1, num_tests + 1):
    num = random.randint(5, 20);
    word = ''.join(random.choices(string.ascii_lowercase, k=num));

    fout.write(word + ' ' + word + '\n')
    
fout.close()
