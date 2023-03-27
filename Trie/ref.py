#!/bin/bash

fin = open("test.in", "r")
fout = open("test.out", "w")

table = {}

for line in fin:
    line = line.replace('\n', '');
    words = line.split()
    
    if(words[0] == 'I'):
        table[words[1]] = 1
        fout.write("Insert: \"" + words[1] + "\".\n")
    elif(words[0] == 'L'):
        if words[1] in table:
            fout.write("Lookup: \"" + words[1] + "\" found.\n")
        else:
            fout.write("Lookup: \"" + words[1] + "\" not found!\n")
    elif(words[0] == 'P'):
        for elem in sorted(table):
            fout.write("Print: \"" + elem + "\".\n")
    elif(words[0] == 'D'):
        if words[1] in table:
            table.pop(words[1])
            fout.write("Delete: \"" + words[1] + "\" deleted.\n")
        else:
            fout.write("Delete: \"" + words[1] + "\" not found!\n")

fin.close()
fout.close()
